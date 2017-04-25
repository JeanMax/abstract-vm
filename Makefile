#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/29 13:16:03 by mcanal            #+#    #+#              #
#    Updated: 2017/04/25 15:38:59 by mc               ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME =		abstractvm

C_NAME =	main.cpp
C_LEX =		lexer.cpp
C_PARS =	parser.cpp operators.cpp
C_CALC =
C_OPE =		OperandFactory.cpp

SRCS =		$(C_NAME)	$(C_LEX)	$(C_PARS)	$(C_CALC)	$(C_OPE)

TEST =		test.sh

VPATH =		src:src/lexer:src/parser:src/calculator:src/operand
O_DIR =		obj
T_DIR =		./test
I_DIR =
OBJS =		$(SRCS:%.cpp=$(O_DIR)/%.o)
DEPS =		$(OBJS:%.o=%.d)


RM =		rm -f
RMDIR =		rmdir
MKDIR =		mkdir -p
MAKE =		make
MAKEFLAGS =	-j 4
CXX =		$(shell clang --version &>/dev/null && echo clang++ || echo g++) -std=c++11
CPPFLAGS =	-Wall -Wextra -Werror
LD =		$(CXX)
LDFLAGS =	$(CPPFLAGS)
LDLIBS =

ifeq ($(OS), Windows_NT)
  CCFLAGS += -D WIN32
  ifeq ($(PROCESSOR_ARCHITECTURE), AMD64)
    CCFLAGS += -D AMD64
  else ifeq ($(PROCESSOR_ARCHITECTURE), x86)
    CCFLAGS += -D IA32
  endif
else
  UNAME_S = $(shell uname -s)
  ifeq ($(UNAME_S), Linux)
    ECHO = echo -e
    CCFLAGS += -D LINUX
  else ifeq ($(UNAME_S), Darwin)
    ECHO = echo
    CCFLAGS += -D OSX
  endif
  UNAME_P = $(shell uname -p)
  ifeq ($(UNAME_P), unknown)
    UNAME_P = $(shell uname -m)
  endif
  ifeq ($(UNAME_P), x86_64)
    CCFLAGS += -D AMD64
  else ifneq ($(filter %86, $(UNAME_P)), )
    CCFLAGS += -D IA32
  else ifneq ($(filter arm%, $(UNAME_P)), )
    CCFLAGS += -D ARM
  endif
endif

WHITE =		\033[37;01m
RED =		\033[31;01m
GREEN =		\033[32;01m
YELLOW =	\033[33;01m
BLUE =		\033[34;01m
BASIC =		\033[0m

FLAGS =			"CPPFLAGS = $(CPPFLAGS)"
COOKIE_FLAGS =	$(O_DIR)/.previous-flag
PREV_FLAGS =	"$(shell cat "$(COOKIE_FLAGS)" 2>/dev/null || echo 'CPPFLAGS = $(CPPFLAGS)')"

ifndef VERBOSE
.SILENT:
endif

.PHONY: all debug sanitize me_cry  re clean fclean mrproper  test

all: $(O_DIR)
ifeq (,$(findstring fsanitize, $(PREV_FLAGS)))
	$(ECHO) $(FLAGS) | grep -q fsanitize && $(MAKE) fclean || true
else
	$(ECHO) $(FLAGS) | grep -qv fsanitize && $(MAKE) fclean || true
endif
	$(ECHO) $(FLAGS) > $(COOKIE_FLAGS)
	$(MAKE) $(NAME) $(FLAGS)

debug: FLAGS = "CPPFLAGS = -g -ggdb"
debug: all

sanitize: FLAGS = "CPPFLAGS = -g -ggdb -fsanitize=address,undefined -ferror-limit=5"
sanitize: all

me_cry: FLAGS = "CPPFLAGS = -Wall -Werror -Wextra -Wpedantic -Wold-style-cast -Woverloaded-virtual -Wfloat-equal -Wwrite-strings -Wcast-align -Wconversion -Wshadow -Weffc++ -Wredundant-decls -Winit-self -Wswitch-default -Wswitch-enum -Wundef -Winline" #-Wcast-qual
me_cry: all

re: FLAGS = $(PREV_FLAGS)
re: fclean all

-include $(DEPS)

$(NAME): $(OBJS)
	@$(ECHO) "$(BLUE)$(OBJS) $(LIBS) $(WHITE)->$(RED) $@ $(BASIC)"
	$(CXX) $(LDFLAGS) $(I_DIR) $(OBJS) $(LDLIBS) -o $@
	@$(ECHO) "$(WHITE)cppflags:$(BASIC) $(CPPFLAGS)"
	@$(ECHO) "$(WHITE)ccpflags:$(BASIC) $(CCPFLAGS)"
	@$(ECHO) "$(WHITE)compi:$(BASIC) $(CXX)"

$(O_DIR)/%.o: %.cpp
	@$(ECHO) "$(WHITE)$<\t->$(BLUE) $@ $(BASIC)"
	$(CXX) $(CCPFLAGS) $(CPPFLAGS) $(I_DIR) -MMD -c $< -o $@

$(O_DIR):
	$(MKDIR) $(O_DIR)


clean:
	$(RM) $(OBJS)
	$(RM) $(DEPS)

fclean: clean
	$(RM) $(NAME)

mrproper: fclean
	$(RM) $(COOKIE_FLAGS)
	$(RMDIR) $(O_DIR)


test: all
	$(T_DIR)/$(TEST)

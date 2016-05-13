BUILD = build

ifneq ($(notdir $(CURDIR)),$(BUILD))

.SUFFIXES:

OBJDIR = $(CURDIR)/$(BUILD)
SRCDIR = $(CURDIR)/src
INCDIR = $(CURDIR)/include
DEPDIR = $(CURDIR)/.d

.PHONY: $(all)
all: $(OBJDIR) $(DEPDIR)
	+@$(MAKE) --no-print-directory -C $< -f $(CURDIR)/Makefile \
	 SRCDIR=$(SRCDIR) INCDIR=$(INCDIR) DEPDIR=$(DEPDIR) $(MAKECMDGOALS)

.PHONY: $(OBJDIR)
$(OBJDIR):
	+@[ -d $@ ] || mkdir -p $@

.PHONY: $(DEPDIR)
$(DEPDIR):
	+@[ -d $@ ] || mkdir -p $@

Makefile : ;

% :: all ;

.PHONY: clean
clean:
	rm -rf $(OBJDIR)
	rm -rf $(DEPDIR)

else

vpath %.c $(SRCDIR)
vpath %.d $(DEPDIR)
vpath %.h $(INCDIR)

TARGET = chopchop

SRC	= $(notdir $(wildcard $(SRCDIR)/*.c))
OBJ = $(SRC:%.c=%.o)
DEP = $(SRC:%.c=$(DEPDIR)/%.d)

CFLAGS  = -std=c99 -Wall -Wextra -Wpedantic -g
CFLAGS += -I$(INCDIR)

.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^

$(DEPDIR)/%.d: %.c
	$(CC) $(CFLAGS) -MM -o $@ $<

-include $(DEP)

endif

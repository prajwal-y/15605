# To build your project, edit this file--not the Makefile!

##################################################
# How to acquire updates.
##################################################
#
# afs - fastest on Andrew machines
# web - will probably work on non-Andrew machines
# offline - if machine has no network access
#
# WARNING - if you miss a staff-issued update
# because you were using "offline", you are
# responsible for the outcome.
#
##################################################
UPDATE_METHOD = afs

##################################################
# Tab stops
##################################################
# If you use tabstops set to something other than
# the international standard of eight characters,
# this is your opportunity to inform our print
# scripts.
TABSTOP = 4

##################################################
# Object files from kern/ which the game AND the
# console tester should link against -- basically,
# the object files which make up your drivers.
##################################################
#
COMMON_OBJS = drivers/install_driver.o drivers/console_driver.o drivers/keyboard_driver.o drivers/timer_driver.o drivers/handler_helper.o

##################################################
# Object files from 410kern/ for just the game
# (in other words, any game-specific helper code
# we release to you--some semesters, there isn't
# any).
##################################################
#
410_GAME_OBJS =

##################################################
# Object files from kern/ for just the game:
# this allows you to break up your game into
# multiple parts.
##################################################
#
KERN_GAME_OBJS = game/game.o game/game_controller.o game/key_handler.o game/screen_painter.o game/gameplay_handler.o

##################################################
# Object files from 410kern/ for just the tester
# (you should not need to change this).
##################################################
#
410TEST_OBJS = 410_test.o

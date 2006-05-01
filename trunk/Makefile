
default:
	@echo Supported build types are:
	@echo debug
	@echo release
	@echo clean
	@echo distclean
	@echo Examples:
	@echo -e \\t make debug
	@echo -e \\t\\t-or-
	@echo -e \\t make release

debug: depend opengui-debug

release: depend opengui-release

clean: opengui-clean depend-clean 

distclean: opengui-distclean depend-distclean 

opengui-clean:
	make -C OpenGUI clean

opengui-distclean:
	make -C OpenGUI distclean

opengui-release:
	make -C OpenGUI release

opengui-debug:
	make -C OpenGUI

depend-clean:
	make -C dependancies/freetype2 clean
	make -C dependancies/corona-linux clean

depend-distclean:
	make -C dependancies/freetype2 distclean
	make -C dependancies/corona-linux distclean

depend:
	@echo "#######################################"
	@echo "       BUILDING DEPENDANCIES"
	@echo "#######################################"
	make dependancies/corona-linux/src/.libs/libcorona.a
	make dependancies/freetype2/objs/.libs/libfreetype.a
	@echo "#######################################"
	@echo "     DONE BUILDING DEPENDANCIES"
	@echo "#######################################"

dependancies/corona-linux/src/.libs/libcorona.a:
	@echo "    ***************************************"
	@echo "                BUILDING CORONA"
	@echo "    ***************************************"
	cd dependancies/corona-linux && ./configure && make && cd -
	@echo "    ***************************************"
	@echo "              DONE BUILDING CORONA"
	@echo "    ***************************************"

dependancies/freetype2/objs/.libs/libfreetype.a:
	@echo "    ***************************************"
	@echo "               BUILDING FREETYPE"
	@echo "    ***************************************"
	cd dependancies/freetype2 && make && make && cd -
	@echo "    ***************************************"
	@echo "             DONE BUILDING FREETYPE"
	@echo "    ***************************************"


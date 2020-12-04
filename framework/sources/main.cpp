/******************************************************************
 __     __    _     _       __    _      _   __
/ /`_  / /\  | |   \ \  /  / /\  | |\ | | | / /`
\_\_/ /_/--\ |_|__  \_\/  /_/--\ |_| \| |_| \_\_,

 Copyright (c) 2020 H. Elwood Gilliland III
 This open source framework is available under the MIT License,
 see LICENSE file accompanying this file for more information
*******************************************************************/

#include "galvanic.h"

#ifndef BUILD_APACHE_MODULE

int main(int argc, char **argv ) {
 InitZeroTypesLibrary();
 Galvanic galvanic;
 return galvanic.Execute( argc, argv );
}

#endif
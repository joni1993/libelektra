/*************************************************************************** 
 *           test_mount.c  - Test suite for testing backend mounting
 *                  -------------------
 *  begin                : Thu Nov 6 2007
 *  copyright            : (C) 2007 by Patrick Sabin
 *  email                : patricksabin@gmx.at
 ****************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the BSD License (revised).                      *
 *                                                                         *
 ***************************************************************************/

#include "yajl.h" // for two functions declared in there

#ifdef HAVE_KDBCONFIG_H
#include "kdbconfig.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <tests_internal.h>

KeySet *getEmptyKeys()
{
	return ksNew(1,
			keyNew("user",
			       KEY_END),
			KS_END
			);
}

KeySet *getNullKeys()
{
	Key *k1, *k2;
	KeySet *ks = ksNew(10,
			keyNew("user",
			       KEY_END),
			keyNew("user/tests",
			       KEY_END),
			keyNew("user/tests/yajl",
			       KEY_END),
			k1 = keyNew("user/tests/yajl/nullkey",
			       KEY_VALUE, "will be removed",
			       KEY_END),
			k2 = keyNew("user/tests/yajl/second_nullkey",
			       KEY_VALUE, "will be removed too",
			       KEY_END),
			KS_END
		);
	keySetBinary(k1, NULL, 0);
	keySetBinary(k2, NULL, 0);

	ksRewind(ks); // shouldn't that be default?
	return ks;
}

KeySet *getBelowKeys()
{
	KeySet *ks = ksNew(10,
			keyNew("user",
			       KEY_END),
			keyNew("user/tests",
			       KEY_END),
			keyNew("user/tests/yajl",
			       KEY_END),
			keyNew("user/tests/yajl/x",
			       KEY_END),
			keyNew("user/tests/yajl/x/y/z",
			       KEY_END),
			keyNew("user/tests/yajl/v",
			       KEY_END),
			keyNew("user/tests/yajl/v/y/z",
			       KEY_END),
			KS_END
		);

	ksRewind(ks); // shouldn't that be default?
	return ks;
}

KeySet *getBooleanKeys()
{
	KeySet *ks = ksNew(10,
			keyNew("user",
			       KEY_END),
			keyNew("user/tests",
			       KEY_END),
			keyNew("user/tests/yajl",
			       KEY_END),
			keyNew("user/tests/yajl/boolean_key",
			       KEY_VALUE, "true",
			       KEY_META, "type", "boolean",
			       KEY_END),
			keyNew("user/tests/yajl/second_boolean_key",
			       KEY_VALUE, "false",
			       KEY_META, "type", "boolean",
			       KEY_END),
			KS_END
		);

	ksRewind(ks);
	return ks;
}

KeySet *getNumberKeys()
{
	KeySet *ks = ksNew(10,
			keyNew("user",
			       KEY_END),
			keyNew("user/tests",
			       KEY_END),
			keyNew("user/tests/yajl",
			       KEY_END),
			keyNew("user/tests/yajl/number_key",
			       KEY_VALUE, "25",
			       KEY_META, "type", "number",
			       KEY_END),
			keyNew("user/tests/yajl/second_number_key",
			       KEY_VALUE, "23002390202",
			       KEY_META, "type", "number",
			       KEY_END),
			keyNew("user/tests/yajl/third_number_key",
			       KEY_VALUE, "230020202.233",
			       KEY_META, "type", "number",
			       KEY_END),
			KS_END
		);

	return ks;
}

KeySet *getStringKeys()
{
	KeySet *ks = ksNew(10,
			keyNew("user",
			       KEY_END),
			keyNew("user/tests",
			       KEY_END),
			keyNew("user/tests/yajl",
			       KEY_END),
			keyNew("user/tests/yajl/string_key",
			       KEY_VALUE, "25",
			       KEY_END),
			keyNew("user/tests/yajl/second_string_key",
			       KEY_VALUE, "some string",
			       KEY_END),
			keyNew("user/tests/yajl/third_string_key",
			       KEY_VALUE, "escape {}; \" \\ problem",
			       KEY_END),
			KS_END
		);

	return ks;
}

KeySet *getMapKeys ()
{
	KeySet *ks = ksNew(10,
			keyNew("user",
			       KEY_END),
			keyNew("user/tests",
			       KEY_END),
			keyNew("user/tests/yajl",
			       KEY_END),
			keyNew("user/tests/yajl/map",
			       KEY_END),
			keyNew("user/tests/yajl/map/string_key",
			       KEY_VALUE, "25",
			       KEY_END),
			keyNew("user/tests/yajl/map/second_string_key",
			       KEY_VALUE, "some string",
			       KEY_END),
			keyNew("user/tests/yajl/map/nested_map",
			       KEY_END),
			keyNew("user/tests/yajl/map/nested_map/string_key",
			       KEY_VALUE, "25",
			       KEY_END),
			keyNew("user/tests/yajl/map/nested_map/second_string_key",
			       KEY_VALUE, "some string",
			       KEY_END),
			keyNew("user/tests/yajl/second_map",
			       KEY_END),
			keyNew("user/tests/yajl/second_map/string_key",
			       KEY_VALUE, "25",
			       KEY_END),
			keyNew("user/tests/yajl/second_map/second_string_key",
			       KEY_VALUE, "some string",
			       KEY_END),
			keyNew("user/tests/yajl/string_key",
			       KEY_VALUE, "25",
			       KEY_END),
			keyNew("user/tests/yajl/second_string_key",
			       KEY_VALUE, "some string",
			       KEY_END),
			KS_END
		);

	return ks;
}

KeySet *getArrayKeys()
{
	KeySet *ks = ksNew(30,
			keyNew("user",
			       KEY_END),
			keyNew("user/tests",
			       KEY_END),
			keyNew("user/tests/yajl",
			       KEY_END),
			keyNew("user/tests/yajl/array",
			       KEY_META, "array", "",
			       KEY_END),
			keyNew("user/tests/yajl/array/#0",
			       KEY_VALUE, "true",
			       KEY_META, "array", "",
			       KEY_META, "type", "boolean",
			       KEY_END),
			keyNew("user/tests/yajl/array/#1",
			       KEY_VALUE, "25",
			       KEY_META, "array", "",
			       KEY_META, "type", "number",
			       KEY_END),
			keyNew("user/tests/yajl/array/#2",
			       KEY_META, "array", "",
			       KEY_VALUE, "some string",
			       KEY_END),
			keyNew("user/tests/yajl/array/#3",
			       KEY_META, "array", "",
			       KEY_VALUE, "0",
			       KEY_META, "type", "number",
			       KEY_END),
			keyNew("user/tests/yajl/array/#4",
			       KEY_META, "array", "",
			       KEY_VALUE, "1",
			       KEY_META, "type", "number",
			       KEY_END),
			keyNew("user/tests/yajl/array/#5",
			       KEY_META, "array", "",
			       KEY_VALUE, "2",
			       KEY_META, "type", "number",
			       KEY_END),
			keyNew("user/tests/yajl/array/#6",
			       KEY_META, "array", "",
			       KEY_VALUE, "3",
			       KEY_META, "type", "number",
			       KEY_END),
			keyNew("user/tests/yajl/array/#7",
			       KEY_META, "array", "",
			       KEY_VALUE, "more \\ a",
			       KEY_END),
			keyNew("user/tests/yajl/array/#8",
			       KEY_META, "array", "",
			       KEY_VALUE, "string \"",
			       KEY_END),
			keyNew("user/tests/yajl/array/#9",
			       KEY_META, "array", "",
			       KEY_VALUE, "string abc",
			       KEY_END),
			keyNew("user/tests/yajl/array/#_10", // hack for keeping sort order
			       KEY_META, "array", "",
			       KEY_VALUE, "def abc",
			       KEY_END),
			keyNew("user/tests/yajl/array/#_11",
			       KEY_META, "array", "",
			       KEY_VALUE, "false",
			       KEY_META, "type", "boolean",
			       KEY_END),
			keyNew("user/tests/yajl/array/#_12",
			       KEY_META, "array", "",
			       KEY_VALUE, "42",
			       KEY_META, "type", "number",
			       KEY_END),
			/*
			keyNew("user/tests/yajl/array/#___333",
			       KEY_END),
			keyNew("user/tests/yajl/array/#_#__#333",
			       KEY_META, "array", "",
			       KEY_VALUE, "42",
			       KEY_META, "type", "number",
			       KEY_END),
			keyNew("user/tests/yajl/array/#______4444", // number of _ not intuitive
			       KEY_END),
			keyNew("user/tests/yajl/array/#_#__#___#4444", // gets quite long... (but works!)
			       KEY_END),
			*/
			KS_END
		);

	return ks;
}

KeySet *getOpenICCKeys()
{
	KeySet *ks = ksNew(60,
			keyNew("user",
			       KEY_END),
			keyNew("user/org",
			       KEY_END),
			keyNew("user/org/freedesktop",
			       KEY_END),
			keyNew("user/org/freedesktop/openicc",
			       KEY_END),

keyNew("user/org/freedesktop/openicc/device",
		KEY_END),
keyNew("user/org/freedesktop/openicc/device/camera",
		KEY_META, "array", "",
		KEY_END),
keyNew("user/org/freedesktop/openicc/device/camera/#0",
		KEY_META, "array", "",
		KEY_END),
keyNew("user/org/freedesktop/openicc/device/camera/#0/prefix",
		KEY_VALUE, "EXIF_",
		KEY_END),
keyNew("user/org/freedesktop/openicc/device/camera/#0/EXIF_model",
		KEY_VALUE, "ShinyGlass", KEY_END),
keyNew("user/org/freedesktop/openicc/device/camera/#0/EXIF_serial",
		KEY_VALUE, "1200000", KEY_END),
keyNew("user/org/freedesktop/openicc/device/camera/#0/EXIF_mnft",
		KEY_VALUE, "GLAS", KEY_END),
keyNew("user/org/freedesktop/openicc/device/camera/#0/EXIF_manufacturer",
		KEY_VALUE, "Glasshuette", KEY_END),
keyNew("user/org/freedesktop/openicc/device/camera/#0/icc_profile",
		KEY_VALUE, "profile_name.icc",
		KEY_END),
keyNew("user/org/freedesktop/openicc/device/camera/#0/creation_date",
		KEY_VALUE, "05/08/11 11:59:50",
		KEY_END),
keyNew("user/org/freedesktop/openicc/device/camera/#0/expire_date",
		KEY_VALUE, "08/08/11 11:59:50",
		KEY_END),
//Typo in example:
//keyNew("user/org/freedesktop/openicc/device/camera/#0/automatic_assignment",
keyNew("user/org/freedesktop/openicc/device/camera/#0/automatic_assigment",
		KEY_VALUE, "1", KEY_END),
keyNew("user/org/freedesktop/openicc/device/camera/#0/comment",
		KEY_VALUE, "nonsense example", KEY_END),

keyNew("user/org/freedesktop/openicc/device/camera/#1",
		KEY_META, "array", "",
		KEY_END),
keyNew("user/org/freedesktop/openicc/device/camera/#1/prefix",
		KEY_VALUE, "EXIF_", KEY_END),
keyNew("user/org/freedesktop/openicc/device/camera/#1/EXIF_model",
		KEY_VALUE, "Knips", KEY_END),
keyNew("user/org/freedesktop/openicc/device/camera/#1/EXIF_serial",
		KEY_VALUE, "3400000", KEY_END),
keyNew("user/org/freedesktop/openicc/device/camera/#1/EXIF_mnft",
		KEY_VALUE, "CON", KEY_END),
keyNew("user/org/freedesktop/openicc/device/camera/#1/EXIF_manufacturer",
		KEY_VALUE, "ConquerLight",
		KEY_END),
keyNew("user/org/freedesktop/openicc/device/camera/#1/icc_profile",
		KEY_VALUE, "profile_name2.icc",
		KEY_END),
keyNew("user/org/freedesktop/openicc/device/camera/#1/creation_date",
		KEY_VALUE, "05/08/11 11:59:50",
		KEY_END),
keyNew("user/org/freedesktop/openicc/device/camera/#1/expire_date",
		KEY_VALUE, "08/08/11 11:59:50",
		KEY_END),
// keyNew("user/org/freedesktop/openicc/device/camera/#1/automatic_assignment",
keyNew("user/org/freedesktop/openicc/device/camera/#1/automatic_assigment",
		KEY_VALUE, "1", KEY_END),

keyNew("user/org/freedesktop/openicc/device/monitor",
		KEY_META, "array", "",
		KEY_END),

keyNew("user/org/freedesktop/openicc/device/monitor/#0",
		KEY_META, "array", "",
		KEY_END),
keyNew("user/org/freedesktop/openicc/device/monitor/#0/prefix",
		KEY_VALUE, "EDID_", KEY_END),
keyNew("user/org/freedesktop/openicc/device/monitor/#0/EDID_mnft_id",
		KEY_VALUE, "12", KEY_END),
keyNew("user/org/freedesktop/openicc/device/monitor/#0/EDID_model_id",
		KEY_VALUE, "123", KEY_END),
keyNew("user/org/freedesktop/openicc/device/monitor/#0/EDID_model",
		KEY_VALUE, "LCD1", KEY_END),
keyNew("user/org/freedesktop/openicc/device/monitor/#0/EDID_serial",
		KEY_VALUE, "ABCD", KEY_END),
keyNew("user/org/freedesktop/openicc/device/monitor/#0/EDID_red_x",
		KEY_VALUE, "0.599609", KEY_END),
keyNew("user/org/freedesktop/openicc/device/monitor/#0/EDID_red_y",
		KEY_VALUE, "0.34375", KEY_END),
keyNew("user/org/freedesktop/openicc/device/monitor/#0/EDID_green_x",
		KEY_VALUE, "0.320312", KEY_END),
keyNew("user/org/freedesktop/openicc/device/monitor/#0/EDID_green_y",
		KEY_VALUE, "0.554688", KEY_END),
keyNew("user/org/freedesktop/openicc/device/monitor/#0/EDID_blue_x",
		KEY_VALUE, "0.150391", KEY_END),
keyNew("user/org/freedesktop/openicc/device/monitor/#0/EDID_blue_y",
		KEY_VALUE, "0.120117", KEY_END),
keyNew("user/org/freedesktop/openicc/device/monitor/#0/EDID_white_x",
		KEY_VALUE, "0.313477", KEY_END),
keyNew("user/org/freedesktop/openicc/device/monitor/#0/EDID_white_y",
		KEY_VALUE, "0.329102", KEY_END),
keyNew("user/org/freedesktop/openicc/device/monitor/#0/EDID_gamma",
		KEY_VALUE, "2.2", KEY_END),
keyNew("user/org/freedesktop/openicc/device/monitor/#0/EDID_mnft",
		KEY_VALUE, "VEN", KEY_END),
keyNew("user/org/freedesktop/openicc/device/monitor/#0/EDID_manufacturer",
		KEY_VALUE, "Vendor1", KEY_END),
keyNew("user/org/freedesktop/openicc/device/monitor/#0/EDID_date",
		KEY_VALUE, "2007-T16", KEY_END),

keyNew("user/org/freedesktop/openicc/device/monitor/#1",
		KEY_META, "array", "", KEY_END),
keyNew("user/org/freedesktop/openicc/device/monitor/#1/prefix",
		KEY_VALUE, "EDID_", KEY_END),
keyNew("user/org/freedesktop/openicc/device/monitor/#1/EDID_mnft_id",
		KEY_VALUE, "34", KEY_END),
keyNew("user/org/freedesktop/openicc/device/monitor/#1/EDID_model_id",
		KEY_VALUE, "456", KEY_END),
keyNew("user/org/freedesktop/openicc/device/monitor/#1/EDID_model",
		KEY_VALUE, "other monitor", KEY_END),
keyNew("user/org/freedesktop/openicc/device/monitor/#1/EDID_serial",
		KEY_VALUE, "other serial", KEY_END),
keyNew("user/org/freedesktop/openicc/device/monitor/#1/EDID_red_x",
		KEY_VALUE, "0.599609", KEY_END),
keyNew("user/org/freedesktop/openicc/device/monitor/#1/EDID_red_y",
		KEY_VALUE, "0.34375", KEY_END),
keyNew("user/org/freedesktop/openicc/device/monitor/#1/EDID_green_x",
		KEY_VALUE, "0.320312", KEY_END),
keyNew("user/org/freedesktop/openicc/device/monitor/#1/EDID_green_y",
		KEY_VALUE, "0.554688", KEY_END),
keyNew("user/org/freedesktop/openicc/device/monitor/#1/EDID_blue_x",
		KEY_VALUE, "0.150391", KEY_END),
keyNew("user/org/freedesktop/openicc/device/monitor/#1/EDID_blue_y",
		KEY_VALUE, "0.120117", KEY_END),
keyNew("user/org/freedesktop/openicc/device/monitor/#1/EDID_white_x",
		KEY_VALUE, "0.313477", KEY_END),
keyNew("user/org/freedesktop/openicc/device/monitor/#1/EDID_white_y",
		KEY_VALUE, "0.329102", KEY_END),
keyNew("user/org/freedesktop/openicc/device/monitor/#1/EDID_gamma",
		KEY_VALUE, "2.2", KEY_END),
keyNew("user/org/freedesktop/openicc/device/monitor/#1/EDID_mnft",
		KEY_VALUE, "NEC", KEY_END),
keyNew("user/org/freedesktop/openicc/device/monitor/#1/EDID_manufacturer",
		KEY_VALUE, "NEC", KEY_END),
keyNew("user/org/freedesktop/openicc/device/monitor/#1/EDID_date",
		KEY_VALUE, "2001-T12", KEY_END),


			KS_END
		);

	return ks;
}

KeySet *getSomePathKeys()
{
	return ksNew(10,
			keyNew("user/some/path/below",
			       KEY_END),
			keyNew("user/some/path/below/tests",
			       KEY_END),
			keyNew("user/some/path/below/tests/yajl",
			       KEY_END),
			keyNew("user/some/path/below/tests/yajl/boolean_key",
			       KEY_VALUE, "true",
			       KEY_META, "type", "boolean",
			       KEY_END),
			keyNew("user/some/path/below/tests/yajl/second_boolean_key",
			       KEY_VALUE, "false",
			       KEY_META, "type", "boolean",
			       KEY_END),
			KS_END);
}


KeySet *modules;

void test_json(const char * fileName,
		     KeySet * compareKeySet,
		     KeySet * conf)
{
	printf ("Test json with %s\n", fileName);

	Plugin *plugin = elektraPluginOpen("yajl", modules, conf, 0);
	exit_if_fail (plugin != 0, "could not open plugin");
	// printf ("Test with %s\n", srcdir_file(fileName));

	Key *parentKey = keyNew ("user/tests/yajl",
			KEY_VALUE, srcdir_file(fileName),
			KEY_END);
	KeySet *keys = ksNew(0);
	succeed_if(plugin->kdbGet(plugin, keys, parentKey) == 1, "kdbGet was not successful");
	succeed_if(output_errors(parentKey), "error in kdbGet");
	succeed_if(output_warnings(parentKey), "warnings in kdbGet");

	compare_keyset(keys, compareKeySet);

	char * fileNameCompare = malloc(strlen(fileName)+6);
	strcat(fileNameCompare, fileName);
	strcat(fileNameCompare, ".comp");
	keySetString(parentKey, srcdir_file(fileNameCompare));
	// printf("File name is: %s\n", keyString(parentKey));

	succeed_if(plugin->kdbSet(plugin, keys, parentKey) == 1, "kdbSet was not successful");
	succeed_if(output_errors(parentKey), "error in kdbSet");
	succeed_if(output_warnings(parentKey), "warnings in kdbSet");
	free(fileNameCompare);

	succeed_if(compare_line_files(srcdir_file(fileName), keyString(parentKey)),
			"files do not match as expected");

	/*
	printf ("The keys we read out are:\n");
	output_keyset(keys);
	printf ("The keys we compared it with:\n");
	output_keyset(compareKeySet);
	*/

	keyDel (parentKey);
	ksDel (keys);
	ksDel (compareKeySet);

	elektraPluginClose(plugin, 0);
}

void test_sibling()
{
	printf ("Test sibling\n");

	Key *x1 = keyNew("user/sw/app/x1", KEY_END);
	Key *x2 = keyNew("user/sw/app/x2", KEY_END);

	succeed_if (elektraKeyIsSibling(x1, x2), "keys should be siblings");

	keySetName(x2, "user/sw/app/ydksaa");
	succeed_if (elektraKeyIsSibling(x1, x2), "keys should be siblings");

	keySetName(x2, "user/sw/app/x1/a");
	succeed_if (!elektraKeyIsSibling(x1, x2), "keys should not be siblings");

	keySetName(x2, "user/sw/apps");
	succeed_if (!elektraKeyIsSibling(x1, x2), "keys should not be siblings");

	keyDel(x1);
	keyDel(x2);
}

void test_array()
{
	printf ("Test array\n");

	Key *k = keyNew("user/array/#0", KEY_END);
	succeed_if(!elektraArrayIncName(k), "increment array entry name returned error");
	succeed_if(!strcmp(keyName(k), "user/array/#1"), "array entry name not correct");
	succeed_if(!elektraArrayIncName(k), "increment array entry name returned error");
	succeed_if(!strcmp(keyName(k), "user/array/#2"), "array entry name not correct");
	succeed_if(!elektraArrayIncName(k), "increment array entry name returned error");
	succeed_if(!strcmp(keyName(k), "user/array/#3"), "array entry name not correct");
	succeed_if(!elektraArrayIncName(k), "increment array entry name returned error");
	succeed_if(!strcmp(keyName(k), "user/array/#4"), "array entry name not correct");
	succeed_if(!elektraArrayIncName(k), "increment array entry name returned error");
	succeed_if(!strcmp(keyName(k), "user/array/#5"), "array entry name not correct");
	succeed_if(!elektraArrayIncName(k), "increment array entry name returned error");
	succeed_if(!strcmp(keyName(k), "user/array/#6"), "array entry name not correct");
	succeed_if(!elektraArrayIncName(k), "increment array entry name returned error");
	succeed_if(!strcmp(keyName(k), "user/array/#7"), "array entry name not correct");
	succeed_if(!elektraArrayIncName(k), "increment array entry name returned error");
	succeed_if(!strcmp(keyName(k), "user/array/#8"), "array entry name not correct");
	succeed_if(!elektraArrayIncName(k), "increment array entry name returned error");
	succeed_if(!strcmp(keyName(k), "user/array/#9"), "array entry name not correct");
	succeed_if(!elektraArrayIncName(k), "increment array entry name returned error");
	succeed_if(!strcmp(keyName(k), "user/array/#_10"), "array entry name not correct");
	succeed_if(!elektraArrayIncName(k), "increment array entry name returned error");
	succeed_if(!strcmp(keyName(k), "user/array/#_11"), "array entry name not correct");
	succeed_if(!elektraArrayIncName(k), "increment array entry name returned error");
	succeed_if(!strcmp(keyName(k), "user/array/#_12"), "array entry name not correct");
	succeed_if(!elektraArrayIncName(k), "increment array entry name returned error");
	succeed_if(!strcmp(keyName(k), "user/array/#_13"), "array entry name not correct");
	keyDel(k);
}

// TODO: make nicer and put to test framework
#define succeed_if_equal(x,y) succeed_if(!strcmp(x,y), x)

void test_nextNotBelow()
{
	printf ("Test next not below\n");

	KeySet *ks = getNullKeys();
	ksRewind(ks);
	Key *k = elektraNextNotBelow(ks);
	succeed_if_equal(keyName(k), "user/tests/yajl/nullkey");
	succeed_if_equal(keyName(ksCurrent(ks)), "user/tests/yajl/nullkey");
	k = elektraNextNotBelow(ks);
	succeed_if_equal(keyName(k), "user/tests/yajl/second_nullkey");
	succeed_if_equal(keyName(ksCurrent(ks)), "user/tests/yajl/second_nullkey");
	k = elektraNextNotBelow(ks);
	succeed_if(k == 0, "not at end of keyset");
	succeed_if(ksCurrent(ks) == 0, "not at end of keyset");
	ksDel (ks);

	ks = getBooleanKeys();
	ksRewind(ks);
	k = elektraNextNotBelow(ks);
	succeed_if_equal(keyName(k), "user/tests/yajl/boolean_key");
	succeed_if_equal(keyName(ksCurrent(ks)), "user/tests/yajl/boolean_key");
	k = elektraNextNotBelow(ks);
	succeed_if_equal(keyName(k), "user/tests/yajl/second_boolean_key");
	succeed_if_equal(keyName(ksCurrent(ks)), "user/tests/yajl/second_boolean_key");
	k = elektraNextNotBelow(ks);
	succeed_if(k == 0, "not at end of keyset");
	succeed_if(ksCurrent(ks) == 0, "not at end of keyset");
	ksDel (ks);

	ks = getBelowKeys();
	ksRewind(ks);
	k = elektraNextNotBelow(ks);
	succeed_if_equal(keyName(k), "user/tests/yajl/v/y/z");
	succeed_if_equal(keyName(ksCurrent(ks)), "user/tests/yajl/v/y/z");
	k = elektraNextNotBelow(ks);
	succeed_if_equal(keyName(k), "user/tests/yajl/x/y/z");
	succeed_if_equal(keyName(ksCurrent(ks)), "user/tests/yajl/x/y/z");
	k = elektraNextNotBelow(ks);
	succeed_if(k == 0, "not at end of keyset");
	succeed_if(ksCurrent(ks) == 0, "not at end of keyset");
	ksDel (ks);

	ks = getMapKeys();
	output_keyset(ks);
	ksRewind(ks);
	k = elektraNextNotBelow(ks);
	succeed_if_equal(keyName(k), "user/tests/yajl/map/nested_map/second_string_key");
	succeed_if_equal(keyName(ksCurrent(ks)), "user/tests/yajl/map/nested_map/second_string_key");
	ksDel (ks);
}

void test_reverseLevel()
{
	Key *k = keyNew("user/abc/defghi/jkl", KEY_END);
	int level=0;
	char buffer[20];

	printf ("Test reverse level\n");

	keyNameReverseIterator it =  elektraKeyNameGetReverseIterator(k);
	while (elektraKeyNameReverseNext(&it))
	{
		level++;

		strncpy(buffer,it.current,it.size);
		buffer[it.size]=0;

		// printf("Level %d name: \"%s\"\n",level,buffer);
		switch (level)
		{
			case 4: succeed_if (strcmp (buffer, "user") == 0, "keyNameGetOneLevel not correct"); break;
			case 3: succeed_if (strcmp (buffer, "abc") == 0, "keyNameGetOneLevel not correct"); break;
			case 2: succeed_if (strcmp (buffer, "defghi") == 0, "keyNameGetOneLevel not correct"); break;
			case 1: succeed_if (strcmp (buffer, "jkl") == 0, "keyNameGetOneLevel not correct"); break;
			default: succeed_if (0, "should not reach case statement");
		}
	}

	keySetName(k,"user////\\/abc/\\/def\\/ghi////jkl\\/\\/");

	level = 0;
	it =  elektraKeyNameGetReverseIterator(k);
	while (elektraKeyNameReverseNext(&it))
	{
		level++;

		strncpy(buffer,it.current,it.size);
		buffer[it.size]=0;

		// printf("Level %d name: \"%s\"\n",level,buffer);
		switch (level)
		{
			case 4: succeed_if (strcmp (buffer, "user") == 0, "keyNameGetOneLevel not correct"); break;
			case 3: succeed_if (strcmp (buffer, "\\/abc") == 0, "keyNameGetOneLevel not correct"); break;
			case 2: succeed_if (strcmp (buffer, "\\/def\\/ghi") == 0, "keyNameGetOneLevel not correct"); break;
			case 1: succeed_if (strcmp (buffer, "jkl\\/\\/") == 0, "keyNameGetOneLevel not correct"); break;
			default: succeed_if (0, "should not reach case statement");
		}
	}

	keyDel (k);
}

void test_countLevel()
{
	Key *k = keyNew("user///", KEY_END);
	succeed_if(elektraKeyCountLevel(k) == 1, "count level wrong");
	keySetName(k, "user/x");
	succeed_if(elektraKeyCountLevel(k) == 2, "count level wrong");
	keySetName(k, "user/x/z/f");
	succeed_if(elektraKeyCountLevel(k) == 4, "count level wrong");
	keySetName(k, "user/x/z\\/f");
	succeed_if(elektraKeyCountLevel(k) == 3, "count level wrong");

	Key *k2 = keyNew("user/x/z", KEY_END);
	succeed_if(elektraKeyCountEqualLevel(k, k2) == 2,
			"equal level wrong");

	keySetName(k,  "user/x/z\\/f");
	keySetName(k2, "user/x/z\\/f");
	succeed_if(elektraKeyCountEqualLevel(k, k2) == 3,
			"equal level wrong");

	keySetName(k,  "user/x/v/ffkkk");
	keySetName(k2, "user/x/v/ff");
	succeed_if(elektraKeyCountEqualLevel(k, k2) == 3,
			"equal level wrong");

	keySetName(k,  "user/x/v/ff");
	keySetName(k2, "user/x/v/ff");
	succeed_if(elektraKeyCountEqualLevel(k, k2) == 4,
			"equal level wrong");

	keySetName(k,  "user/x\\abc/v/ff");
	keySetName(k2, "user/x\\abc/v/ff");
	succeed_if(elektraKeyCountEqualLevel(k, k2) == 4,
			"equal level wrong");

	keyDel(k);
	keyDel(k2);
}

void test_writing()
{
	KeySet *conf = ksNew(0);
	Key *parentKey = keyNew("user",
				KEY_VALUE, "/proc/self/fd/1",
				KEY_END);

	Plugin *plugin = elektraPluginOpen("yajl", modules, conf, 0);
	exit_if_fail (plugin != 0, "could not open plugin");

	succeed_if(plugin->kdbSet(plugin, getNullKeys(), parentKey) == 1, "kdbSet was not successful");
	succeed_if(plugin->kdbSet(plugin, getBooleanKeys(), parentKey) == 1, "kdbSet was not successful");
	succeed_if(plugin->kdbSet(plugin, getNumberKeys(), parentKey) == 1, "kdbSet was not successful");
	succeed_if(plugin->kdbSet(plugin, getStringKeys(), parentKey) == 1, "kdbSet was not successful");
	// succeed_if(plugin->kdbSet(plugin, getMapKeys(), parentKey) == 1, "kdbSet was not successful");
}

int main(int argc, char** argv)
{
	printf("YAJL       TESTS\n");
	printf("==================\n\n");

	modules = ksNew(0);
	elektraModulesInit(modules, 0);

	init (argc, argv);

	test_array();
	test_sibling();
	test_nextNotBelow();
	test_reverseLevel();
	test_countLevel();
	test_writing();

	/*
	test_json("examples/testdata_null.json", getNullKeys(), ksNew(0));
	test_json("examples/testdata_boolean.json", getBooleanKeys(), ksNew(0));
	test_json("examples/testdata_number.json", getNumberKeys(), ksNew(0));
	test_json("examples/testdata_string.json", getStringKeys(), ksNew(0));
	test_json("examples/testdata_maps.json", getMapKeys(), ksNew(0));
	test_json("examples/testdata_array.json", getArrayKeys(), ksNew(0));
	test_json("examples/OpenICC_device_config_DB.json", getOpenICCKeys(), ksNew(0));
	test_json("examples/testdata_boolean.json", getSomePathKeys(),
		ksNew(1, keyNew("system/user_path", KEY_VALUE, "user/some/path/below", KEY_END), KS_END));
	*/


	elektraModulesClose(modules, 0);
	ksDel (modules);

	printf("\ntest_yajl RESULTS: %d test(s) done. %d error(s).\n", nbTest, nbError);

	return nbError;
}


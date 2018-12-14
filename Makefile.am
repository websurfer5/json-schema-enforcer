# Makefile.am
#
# Copyright (c) 2018 Jeffrey Kintscher <websurfer@surf2c.net>
#
#    Licensed under the Apache License, Version 2.0 (the "License");
#    you may not use this file except in compliance with the License.
#    You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
#    Unless required by applicable law or agreed to in writing, software
#    distributed under the License is distributed on an "AS IS" BASIS,
#    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#    See the License for the specific language governing permissions and
#    limitations under the License.

ACLOCAL_AMFLAGS = -I m4
YACC_ERROR = ${BISON_OPTS}
AM_YFLAGS = ${YACC_ERROR} $(YFLAGS) --report=all 
AC_CFLAGS = -ansi -pipe
AC_CXXFLAGS = -ansi -pipe
AM_CPPFLAGS = -I$(top_srcdir)/${LIB_INCLUDE} -I$(top_builddir)/${LIB_INCLUDE} -I$(top_srcdir)/src/include -I$(top_builddir)/src/include -I$(top_builddir)/src/schema -I$(top_srcdir)/src/schema ${BOOST_CPPFLAGS}
AM_LDFLAGS = $(LDFLAGS) ${BOOST_LDFLAGS} ${BOOST_LIBS}

EXTRA_DIST = src/schema/schema-lexer.ll \
             src/schema/schema-parser.yy \
             $(JSON_INPUT_FILES) \
             $(EMIT_PARSER_OUTPUT_FILES) \
             LICENSE

GENERATED_FILES = \
				src/schema/schema-lexer.cc \
				src/schema/schema-lexer.hh \
				src/schema/schema-parser.cc \
				src/schema/schema-parser.hh \
				src/progs/def-emit-parser-json-input.hh

JSON_PARSER_INPUT_DIR = tests/json/emit-parser-inputs
JSON_PARSER_INPUT_FILES = $(wildcard $(top_srcdir)/$(JSON_PARSER_INPUT_DIR)/*.json)
JSON_PARSER_INPUT_CC_FILES = $(patsubst %.json,$(top_builddir)/$(JSON_PARSER_INPUT_DIR)/%.cc,$(notdir $(JSON_PARSER_INPUT_FILES)))
JSON_PARSER_INPUT_O_FILES = $(patsubst %.json,$(top_builddir)/$(JSON_PARSER_INPUT_DIR)/%.$(OBJEXT),$(notdir $(JSON_PARSER_INPUT_FILES)))
JSON_SCHEMA_INPUT_DIR = tests/json/parse-schema-inputs
JSON_SCHEMA_INPUT_FILES = $(wildcard $(top_srcdir)/$(JSON_SCHEMA_INPUT_DIR)/*.json)
JSON_SCHEMA_INPUT_CC_FILES = $(patsubst %.json,$(top_builddir)/$(JSON_SCHEMA_INPUT_DIR)/%.cc,$(notdir $(JSON_SCHEMA_INPUT_FILES)))
JSON_SCHEMA_INPUT_O_FILES = $(patsubst %.json,$(top_builddir)/$(JSON_SCHEMA_INPUT_DIR)/%.$(OBJEXT),$(notdir $(JSON_SCHEMA_INPUT_FILES)))
JSON_INPUT_FILES = \
				$(JSON_PARSER_INPUT_FILES)		\
				$(JSON_SCHEMA_INPUT_FILES)
JSON_INPUT_CC_FILES = \
				$(JSON_PARSER_INPUT_CC_FILES)	\
				$(JSON_SCHEMA_INPUT_CC_FILES)
JSON_INPUT_O_FILES = \
				$(JSON_PARSER_INPUT_O_FILES)	\
				$(JSON_SCHEMA_INPUT_O_FILES)
EMIT_PARSER_OUTPUT_FILES_PARSER = $(wildcard $(srcdir)/tests/emit-parser-output/parser-*.yy)
EMIT_PARSER_OUTPUT_FILES_LEXER = $(wildcard $(srcdir)/tests/emit-parser-output/lexer-*.ll)
EMIT_PARSER_OUTPUT_FILES_STYPE = $(wildcard $(srcdir)/tests/emit-parser-output/stype-*.hh)
EMIT_PARSER_OUTPUT_FILES = \
				$(EMIT_PARSER_OUTPUT_FILES_LEXER)  \
				$(EMIT_PARSER_OUTPUT_FILES_PARSER) \
				$(EMIT_PARSER_OUTPUT_FILES_STYPE)
# EMIT_PARSER_OUTPUT_FILES = $(wildcard $(srcdir)/tests/emit-parser-output/*.txt)
EMIT_PARSER_OUTPUT_CC_FILES = $(patsubst %.ll,$(top_builddir)/tests/emit-parser-output/build/lib/%.cc,$(notdir $(EMIT_PARSER_OUTPUT_FILES_LEXER)))
EMIT_PARSER_OUTPUT_CC_FILES += $(patsubst %.yy,$(top_builddir)/tests/emit-parser-output/build/lib/%.cc,$(notdir $(EMIT_PARSER_OUTPUT_FILES_PARSER)))
EMIT_PARSER_OUTPUT_CC_FILES += $(patsubst %.hh,$(top_builddir)/tests/emit-parser-output/build/lib/%.cc,$(notdir $(EMIT_PARSER_OUTPUT_FILES_STYPE)))
EMIT_PARSER_OUTPUT_O_FILES = $(patsubst %.cc,$(top_builddir)/tests/emit-parser-output/build/lib/%.$(OBJEXT),$(notdir $(EMIT_PARSER_OUTPUT_CC_FILES)))
GENERATED_TEST_FILES =	$(JSON_INPUT_CC_FILES) \
						$(EMIT_PARSER_OUTPUT_CC_FILES) \
						$(top_builddir)/tests/include/json-strings.hh \
						$(top_builddir)/tests/include/emit-parser-output-strings.hh \
						$(top_builddir)/tests/include/def-emit-parser-tests.hh

BUILT_SOURCES =	\
				$(GENERATED_FILES) \
				$(GENERATED_TEST_FILES)

SCHEMA_FILES = src/include/FormatType.hh \
			   src/include/FormatType-vars.hh \
			   src/include/ItemType.hh \
			   src/include/ItemType-vars.hh \
			   src/include/JsonItem.hh \
			   src/include/ParsedItemData.hh \
			   src/include/ParsedItemData-vars.hh \
			   src/include/SchemaData.hh \
			   src/include/SchemaItem.hh \
			   src/include/SchemaItem-vars.hh \
			   src/include/SchemaObject.hh \
			   src/include/schema-stype.hh \
			   src/include/stddefs.hh \
			   src/include/Token.hh \
			   src/include/Token-vars.hh \
			   src/include/yyscan.hh \
			   src/schema/FormatType.cc \
			   src/schema/ItemType.cc \
			   src/schema/JsonItem.cc \
			   src/schema/ParsedItemData.cc \
			   src/schema/SchemaData.cc \
			   src/schema/SchemaItem.cc \
			   src/schema/SchemaObject.cc \
			   src/schema/Token.cc \
			   $(GENERATED_FILES)

bin_PROGRAMS = json-schema-tool
lib_LTLIBRARIES = libjson-schema-code-gen.la

json_schema_tool_LDADD = ${lib_LTLIBRARIES} ${top_builddir}/tests/json/libsamplejson.a
json_schema_tool_LDFLAGS = $(AM_LDFLAGS)
json_schema_tool_CPPFLAGS = $(AM_CPPFLAGS) -I$(top_srcdir)/src/progs -I$(top_builddir)/src/progs
json_schema_tool_SOURCES =  src/progs/json-schema-tool.cc \
							$(top_builddir)/tests/include/json-strings.hh

libjson_schema_code_gen_la_SOURCES = 	$(SCHEMA_FILES)
libjson_schema_code_gen_la_CPPFLAGS = 	$(AM_CPPFLAGS) $(FLEX_CPPFLAGS)

CLEANFILES = $(GENERATED_FILES) \
			 $(GENERATED_TEST_FILES) \
			 $(JSON_INPUT_O_FILES) \
			 $(EMIT_PARSER_OUTPUT_O_FILES) \
			 src/schema/*.*_bak \
			 src/schema/*.output

clean-local:	clean-local-check

.PHONY:	clean-local-check

clean-local-check:
	rm -rf $(top_builddir)/$(JSON_PARSER_INPUT_DIR)/$(DEPDIR)
	rm -rf $(top_builddir)/$(JSON_SCHEMA_INPUT_DIR)/$(DEPDIR)
	rm -rf $(top_builddir)/tests/emit-parser-output/build/lib/$(DEPDIR)
	rm -rf $(top_builddir)/tests/*.dSYM

TESTS = tests/unittclasses \
		tests/unittemitparser \
		tests/unittoutput \
		tests/unittparseschema

check_PROGRAMS = $(TESTS)
noinst_LIBRARIES = \
				tests/json/libsamplejson.a \
				tests/liboutputstrings.a

TESTS_CPP_FLAGS = $(AM_CPPFLAGS) -I$(top_srcdir)/tests/include -I$(top_builddir)/tests/include

tests_json_libsamplejson_a_LIBADD = $(JSON_INPUT_O_FILES)
tests_json_libsamplejson_a_CPPFLAGS = $(TESTS_CPP_FLAGS)
tests_json_libsamplejson_a_SOURCES = $(JSON_INPUT_FILES)

tests_liboutputstrings_a_LIBADD = $(EMIT_PARSER_OUTPUT_O_FILES)
tests_liboutputstrings_a_CPPFLAGS = $(TESTS_CPP_FLAGS)
tests_liboutputstrings_a_SOURCES = $(EMIT_PARSER_OUTPUT_FILES)

tests_unittoutput_LDFLAGS = $(AM_LDFLAGS) -static
tests_unittoutput_CPPFLAGS = -I$(top_builddir)/src/templates -I$(top_srcdir)/src/templates $(TESTS_CPP_FLAGS)
tests_unittoutput_CXXFLAGS = $(AM_CXXFLAGS)
tests_unittoutput_SOURCES = \
					tests/unittest.cc \
					src/templates/json.hh \
					src/templates/json.cc \
					tests/output/test-Json-class.cc

tests_unittclasses_LDADD = libjson-schema-code-gen.la
tests_unittclasses_LDFLAGS = $(AM_LDFLAGS) -static
tests_unittclasses_CPPFLAGS = $(TESTS_CPP_FLAGS)
tests_unittclasses_CXXFLAGS = $(AM_CXXFLAGS) -Wno-parentheses -Wno-error=parentheses
tests_unittclasses_SOURCES = \
					tests/unittest.cc \
					tests/include/flag-macros.hh \
					tests/include/var-obj-macros.hh \
					tests/classes/test-FormatType-class.cc \
					tests/classes/test-ItemType-class.cc \
					tests/classes/test-JsonItem-class.cc \
					tests/classes/test-ParsedItemData-class.cc \
					tests/classes/test-SchemaItem-class.cc \
					tests/classes/test-Token-class.cc

tests_unittparseschema_LDADD = \
					libjson-schema-code-gen.la \
					tests/json/libsamplejson.a
tests_unittparseschema_LDFLAGS = $(AM_LDFLAGS) -static
tests_unittparseschema_CPPFLAGS = $(TESTS_CPP_FLAGS)
tests_unittparseschema_CXXFLAGS = $(AM_CXXFLAGS) -Wno-parentheses -Wno-error=parentheses
tests_unittparseschema_SOURCES = \
					tests/unittest.cc \
					tests/parse-schema/test-parse-schema-integer.cc \
					tests/parse-schema/test-parse-schema-number.cc \
					tests/parse-schema/test-parse-schema-string.cc

tests_unittemitparser_LDADD = \
					libjson-schema-code-gen.la \
					tests/json/libsamplejson.a \
					tests/liboutputstrings.a
tests_unittemitparser_LDFLAGS = $(AM_LDFLAGS) -static
tests_unittemitparser_CPPFLAGS = $(TESTS_CPP_FLAGS)
tests_unittemitparser_CXXFLAGS = $(AM_CXXFLAGS) -Wno-parentheses -Wno-error=parentheses
tests_unittemitparser_SOURCES = \
					tests/unittest.cc \
					tests/include/def-emit-parser-tests.hh \
					tests/include/emit-parser-output-strings.hh \
					tests/parser-gen/test-emit-parser.cc

SED_IN_PLACE_FLAG='-i.sed_bak'

src/schema/schema-parser.hh:	src/schema/schema-parser.cc Makefile

%-parser.cc:	%-parser.yy %-lexer.ll
	$(YACC) $(AM_YFLAGS) --defines=$(basename $@).hh -o $@ $<

src/schema/schema-lexer.hh:	src/schema/schema-lexer.cc Makefile

src/schema/schema-lexer.cc:	src/schema/schema-lexer.ll
	$(LEX) -o $@ --header-file=$(basename $@).hh --never-interactive $<
	$(SED) -e 's/YYSTYPE/SCHEMA_PARSER_STYPE/g' $(SED_IN_PLACE_FLAG) $(basename $@).hh
	$(SED) -e 's/YYSTYPE/SCHEMA_PARSER_STYPE/g' $(SED_IN_PLACE_FLAG) $@

JSON_SCHEMA_INPUT_STRING_PREFIX = str_schema_input_json_
JSON_PARSER_INPUT_STRING_PREFIX = str_parser_input_json_

$(JSON_SCHEMA_INPUT_DIR)/%.cc:	$(JSON_SCHEMA_INPUT_DIR)/%.json Makefile
	mkdir -p $(dir $@) $(dir $@)/.deps
	echo "//" $(notdir $@) > $@
	echo "//" >> $@
	echo "// ** generated file - do not edit! **" >> $@
	echo "#include <string>" >> $@
	echo "extern const std::string $(JSON_SCHEMA_INPUT_STRING_PREFIX)$(subst -,_,$(basename $(notdir $@))) =" >> $@
	$(SED) -e 's/["\\]/\\&/g' -e 's/$$/\\n"/g' -e 's/^/"/' $< >> $@
	echo "\"\";" >> $@

$(JSON_PARSER_INPUT_DIR)/%.cc:	$(JSON_PARSER_INPUT_DIR)/%.json Makefile
	mkdir -p $(dir $@) $(dir $@)/.deps
	echo "//" $(notdir $@) > $@
	echo "//" >> $@
	echo "// ** generated file - do not edit! **" >> $@
	echo "#include <string>" >> $@
	echo "extern const std::string $(JSON_PARSER_INPUT_STRING_PREFIX)$(subst -,_,$(basename $(notdir $@))) =" >> $@
	$(SED) -e 's/["\\]/\\&/g' -e 's/$$/\\n"/g' -e 's/^/"/' $< >> $@
	echo "\"\";" >> $@

tests/include/json-strings.hh:	$(JSON_INPUT_FILES) $(JSON_INPUT_CC_FILES) Makefile
	mkdir -p $(dir $@) $(dir $@)/.deps
	echo "//" $(notdir $@) > $@
	echo "//" >> $@
	echo "// ** generated file - do not edit! **" >> $@
	echo "#ifndef __JSONSCHEMAENFORCER_JSON_SCHEMA_INPUT_STRINGS_HH" >> $@
	echo "#define __JSONSCHEMAENFORCER_JSON_SCHEMA_INPUT_STRINGS_HH" >> $@
	echo "#include <string>" >> $@
	for i in $(subst -,_,$(basename $(notdir $(JSON_SCHEMA_INPUT_FILES)))) ; do echo "extern const std::string $(JSON_SCHEMA_INPUT_STRING_PREFIX)$${i};" >> $@ ; done
	for i in $(subst -,_,$(basename $(notdir $(JSON_PARSER_INPUT_FILES)))) ; do echo "extern const std::string $(JSON_PARSER_INPUT_STRING_PREFIX)$${i};" >> $@ ; done
	echo "#endif   // __JSONSCHEMAENFORCER_JSON_SCHEMA_INPUT_STRINGS_HH" >> $@

src/progs/def-emit-parser-json-input.hh:	$(JSON_PARSER_INPUT_FILES) Makefile
	mkdir -p $(dir $@) $(dir $@)/.deps
	echo "//" $(notdir $@) > $@
	echo "//" >> $@
	echo "// ** generated file - do not edit! **" >> $@
	echo "#include <string>" >> $@
	for i in $(subst -,_,$(basename $(notdir $(JSON_PARSER_INPUT_FILES)))) ; do echo "DEF_TEXT_TEST($${i})" >> $@ ; done
#	for i in $(basename $(notdir $(JSON_PARSER_INPUT_FILES))) ; do _NAME=$$(echo "$${i}" | sed 's/-/_/g') ; echo "DEF_TEXT_TEST($${i}, $${_NAME})" >> $@ ; done

OUTPUT_TEXT_PREFIX = str_output_text_

$(top_builddir)/$(JSON_PARSER_INPUT_DIR) \
$(top_builddir)/$(JSON_SCHEMA_INPUT_DIR) \
$(JSON_PARSER_INPUT_DIR)/$(DEPDIR) \
$(JSON_SCHEMA_INPUT_DIR)/$(DEPDIR) \
tests/emit-parser-output/$(DEPDIR):
	mkdir -p $@

# $(JSON_SCHEMA_INPUT_DIR)/$(DEPDIR):
# 	mkdir -p $@

# tests/emit-parser-output/$(DEPDIR):
# 	mkdir -p $@

tests/emit-parser-output/build/lib/%.cc:	$(srcdir)/tests/emit-parser-output/%.yy Makefile #tests/include/emit-parser-output-strings.hh
	mkdir -p $(dir $@) $(dir $@)/.deps
	echo "// ** generated file - do not edit! **" > $@
	echo "#include <string>" >> $@
	echo "extern const std::string $(OUTPUT_TEXT_PREFIX)$(subst -,_,$(basename $(notdir $@))) =" >> $@
	$(SED) -e 's/["\\]/\\&/g' -e 's/$$/\\n"/g' -e 's/^/\"/' $< >> $@
	echo "\"\";" >> $@

tests/emit-parser-output/build/lib/%.cc:	$(srcdir)/tests/emit-parser-output/%.ll Makefile #tests/include/emit-parser-output-strings.hh
	mkdir -p $(dir $@) $(dir $@)/.deps
	echo "// ** generated file - do not edit! **" > $@
	echo "#include <string>" >> $@
	echo "extern const std::string $(OUTPUT_TEXT_PREFIX)$(subst -,_,$(basename $(notdir $@))) =" >> $@
	$(SED) -e 's/["\\]/\\&/g' -e 's/$$/\\n"/g' -e 's/^/\"/' $< >> $@
	echo "\"\";" >> $@

tests/emit-parser-output/build/lib/%.cc:	$(srcdir)/tests/emit-parser-output/%.hh Makefile #tests/include/emit-parser-output-strings.hh
	mkdir -p $(dir $@) $(dir $@)/.deps
	echo "// ** generated file - do not edit! **" > $@
	echo "#include <string>" >> $@
	echo "extern const std::string $(OUTPUT_TEXT_PREFIX)$(subst -,_,$(basename $(notdir $@))) =" >> $@
	$(SED) -e 's/["\\]/\\&/g' -e 's/$$/\\n"/g' -e 's/^/\"/' $< >> $@
	echo "\"\";" >> $@

tests/include/emit-parser-output-strings.hh:	$(EMIT_PARSER_OUTPUT_FILES) Makefile
	mkdir -p $(dir $@) $(dir $@)/.deps
	echo "//" $(notdir $@) > $@
	echo "//" >> $@
	echo "// ** generated file - do not edit! **" >> $@
	echo "#ifndef __JSONSCHEMAENFORCER_EMIT_PARSER_OUTPUT_STRINGS_HH" >> $@
	echo "#define __JSONSCHEMAENFORCER_EMIT_PARSER_OUTPUT_STRINGS_HH" >> $@
	echo "#include <string>" >> $@
	for i in $(subst -,_,$(basename $(notdir $(EMIT_PARSER_OUTPUT_FILES_LEXER)))) ; do echo "extern const std::string $(OUTPUT_TEXT_PREFIX)$${i};" >> $@ ; done
	for i in $(subst -,_,$(basename $(notdir $(EMIT_PARSER_OUTPUT_FILES_PARSER)))) ; do echo "extern const std::string $(OUTPUT_TEXT_PREFIX)$${i};" >> $@ ; done
	for i in $(subst -,_,$(basename $(notdir $(EMIT_PARSER_OUTPUT_FILES_STYPE)))) ; do echo "extern const std::string $(OUTPUT_TEXT_PREFIX)$${i};" >> $@ ; done
	echo "#endif   // __JSONSCHEMAENFORCER_EMIT_PARSER_OUTPUT_STRINGS_HH" >> $@

tests/include/def-emit-parser-tests.hh:	$(EMIT_PARSER_OUTPUT_FILES) Makefile
	mkdir -p $(dir $@) $(dir $@)/.deps
	echo "//" $(notdir $@) > $@
	echo "//" >> $@
	echo "// ** generated file - do not edit! **" >> $@
	for i in $(subst lexer-,,$(filter lexer-%,$(basename $(notdir $(EMIT_PARSER_OUTPUT_FILES_LEXER))))) ; do _NAME=$$(echo "$${i}" | sed 's/-/_/g') ; echo "DEF_TEXT_TEST($${i}, $${_NAME})" >> $@ ; done

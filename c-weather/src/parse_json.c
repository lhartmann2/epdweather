#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/jsmn.h"
#include "include/Parsed_Json.h"
#include "include/errmsg.h"

/**
 * Parse a json string with jsmn lib.
 * @see https://github.com/zserge/jsmn
 * for parsing implementation detail.
 * Return the parsed tokens.
 *
 * @param int number_of_tokens
 * @param char * data
 * @return jsmntok_t * tokens
 */
struct Parsed_Json *parse_json(char *data, int number_of_tokens)
{
	jsmn_parser parser;
	struct Parsed_Json *parsed;

	jsmn_init(&parser);

	// Calculate the memory required for the tokens
	size_t size = sizeof(jsmntok_t) * number_of_tokens;
	jsmntok_t *tokens = malloc(size);

	int result =
	    jsmn_parse(&parser, data, strlen(data), tokens, number_of_tokens);

	if (result < 0) {
		errmsg("Failed to parse JSON");
		return NULL;
	}

	if (tokens[0].type != JSMN_ARRAY && tokens[0].type != JSMN_OBJECT) {
		errmsg("The first element should be an array or an object");
		return NULL;
	}

	parsed = malloc(sizeof(*parsed));
	parsed->number_of_tokens = result;
	parsed->tokens = tokens;

	return parsed;
}

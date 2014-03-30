/*
 * jp_attribute_parse.h
 *
 *  Created on: Sep 12, 2013
 *      Author: along
 */

#ifndef JP_ATTRIBUTE_PARSE_H_
#define JP_ATTRIBUTE_PARSE_H_

int32_t json_parse_attribute_property_attribute_name(json_t*json_name,
		jp_tag_attribute_t*attribute);

int32_t json_parse_attribute_property_type(json_t*json_type,
		jp_tag_attribute_t*attribute);

int32_t json_parse_attribute_property_require(json_t*json_type,
		jp_tag_attribute_t*attribute);

int32_t json_parse_attribute_property_comment(json_t*json_type,
		jp_tag_attribute_t*attribute);

int32_t json_parse_attribute(json_t* json_attribute,
		jp_tag_attribute_t*attribute);

#endif /* JP_ATTRIBUTE_PARSE_H_ */

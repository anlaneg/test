/*
 * jp_tag_parse.h
 *
 *  Created on: Sep 12, 2013
 *      Author: along
 */

#ifndef JP_TAG_PARSE_H_
#define JP_TAG_PARSE_H_

int32_t json_parse_property_parent(json_t* json_parent, jp_tag_t* tag);

int32_t json_parse_property_require(json_t* json_require, jp_tag_t*tag);

int32_t json_parse_property_comment(json_t* json_comment, jp_tag_t*tag);

int32_t json_parse_property_attribute(json_t* json_attribute, jp_tag_t*tag);

int32_t json_parse_property_tag(json_t* json_tag, jp_tag_t*tag);

#endif /* JP_TAG_PARSE_H_ */

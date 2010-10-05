#ifndef DNS_ERROR_HPP
#define DNS_ERROR_HPP

namespace dns
{
/**
* @brief Application errors
*/
	enum eDNSError
	{
		ERR_NONE = 0,                                                           /* No error */
		ERR_INTERNAL,                                                           /* "Internal error" */
		ERR_Q_BUFFER_OVERFLOW,                                  /* "Input name buffer overflow" */
		ERR_Q_INVALID_COMPRESSION,                              /* "Invalid compression method" */
		ERR_Q_NAME_TOO_LONG,                                            /* "Question name too long" */
		ERR_LABEL_TOO_LONG,                                   			/* "Label too long" */
		ERR_NO_CLASS,                                                           /* "Unknown class" */
		ERR_NAME_FORMAT,                                                        /* "Invalid name format" */
		ERR_INVALID_TYPE,                                                       /* "Invalid type" */
		ERR_INVALID_CLASS,                                              /* "Invalid class" */
		ERR_NO_QUESTION,                                                        /* "No question in query" */
		ERR_MULTI_QUESTIONS,                                            /* "Multiple questions in query" */
		ERR_QUESTION_TRUNCATED,                                 /* "Question truncated" */
		ERR_UNSUPPORTED_OPCODE,                                 /* "Unsupported opcode" */
		ERR_UNSUPPORTED_TYPE,                                   /* "Unsupported type" */
		ERR_UNSUPPORTED_CLASS,                                   /* "Unsupported type" */
		ERR_MALFORMED_REQUEST,                                  /* "Malformed request" */
		ERR_RESPONSE_BIT_SET,                                   /* "Response bit set on query" */
		ERR_NOT_IMPLEMENTED
	};
}

#endif


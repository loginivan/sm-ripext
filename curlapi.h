/**
 * vim: set ts=4 :
 * =============================================================================
 * SourceMod REST in Pawn Extension
 * Copyright 2017 Erik Minekus
 * =============================================================================
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SM_RIPEXT_CURLAPI_H_
#define SM_RIPEXT_CURLAPI_H_

#include "extension.h"

class HTTPClient
{
public:
	HTTPClient(const char *baseURL) : baseURL(baseURL) {}

	char *BuildURL(const char *endpoint);

	struct curl_slist *GetHeaders(struct HTTPRequest request);

	void Request(struct HTTPRequest request, IPluginFunction *function, cell_t value);

private:
	const char *baseURL;
};

#endif // SM_RIPEXT_CURLAPI_H_

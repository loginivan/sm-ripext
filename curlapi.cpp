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

#include "curlapi.h"
#include "curlthread.h"

char *HTTPClient::BuildURL(const char *endpoint)
{
	char *url = new char[strlen(this->baseURL) + strlen(endpoint) + 2];
	strcpy(url, this->baseURL);
	strcat(url, "/");
	strcat(url, endpoint);

	return url;
}

struct curl_slist *HTTPClient::GetHeaders(struct HTTPRequest request)
{
	struct curl_slist *headers = NULL;
	headers = curl_slist_append(headers, "Accept: application/json");
	headers = curl_slist_append(headers, "Content-Type: application/json");

	char header[32];
	smutils->Format(header, sizeof(header), "Content-Length: %d", request.size);
	headers = curl_slist_append(headers, header);

	return headers;
}

void HTTPClient::Request(struct HTTPRequest request, IPluginFunction *function, cell_t value)
{
	IChangeableForward *forward = forwards->CreateForwardEx(NULL, ET_Ignore, 2, NULL, Param_Cell, Param_Cell);
	forward->AddFunction(function);

	HTTPRequestThread *thread = new HTTPRequestThread(this, request, forward, value);
	threader->MakeThread(thread);
}

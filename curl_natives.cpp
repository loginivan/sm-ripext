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

#include "extension.h"
#include "curlapi.h"

static cell_t CreateHTTPClientObject(IPluginContext *pContext, const cell_t *params)
{
	char *baseUrl;
	pContext->LocalToString(params[1], &baseUrl);

	HTTPClient *client = new HTTPClient(baseUrl);

	Handle_t hndl = handlesys->CreateHandle(htHTTPClientObject, client, pContext->GetIdentity(), myself->GetIdentity(), NULL);
	if (hndl == BAD_HANDLE)
	{
		pContext->ThrowNativeError("Could not create HTTP client handle.");
		return BAD_HANDLE;
	}

	return hndl;
}

static cell_t HTTPGetRequest(IPluginContext *pContext, const cell_t *params)
{
	HandleError err;
	HandleSecurity sec(pContext->GetIdentity(), myself->GetIdentity());

	HTTPClient *client;
	Handle_t hndlClient = static_cast<Handle_t>(params[1]);
	if ((err=handlesys->ReadHandle(hndlClient, htHTTPClientObject, &sec, (void **)&client)) != HandleError_None)
	{
		return pContext->ThrowNativeError("Invalid HTTP client handle %x (error %d)", hndlClient, err);
	}

	char *endpoint;
	pContext->LocalToString(params[2], &endpoint);

	IPluginFunction *callback = pContext->GetFunctionById(params[3]);
	cell_t value = params[4];

	struct HTTPRequest request("GET", endpoint);

	client->Request(request, callback, value);

	return 1;
}

static cell_t HTTPPostRequest(IPluginContext *pContext, const cell_t *params)
{
	HandleError err;
	HandleSecurity sec(pContext->GetIdentity(), myself->GetIdentity());

	HTTPClient *client;
	Handle_t hndlClient = static_cast<Handle_t>(params[1]);
	if ((err=handlesys->ReadHandle(hndlClient, htHTTPClientObject, &sec, (void **)&client)) != HandleError_None)
	{
		return pContext->ThrowNativeError("Invalid HTTP client handle %x (error %d)", hndlClient, err);
	}

	char *endpoint;
	pContext->LocalToString(params[2], &endpoint);

	json_t *data;
	Handle_t hndlData = static_cast<Handle_t>(params[3]);
	if ((err=handlesys->ReadHandle(hndlData, htJSONObject, &sec, (void **)&data)) != HandleError_None)
	{
		return pContext->ThrowNativeError("Invalid data handle %x (error %d)", hndlData, err);
	}

	IPluginFunction *callback = pContext->GetFunctionById(params[4]);
	cell_t value = params[5];

	struct HTTPRequest request("POST", endpoint, data);

	client->Request(request, callback, value);

	return 1;
}

static cell_t HTTPPutRequest(IPluginContext *pContext, const cell_t *params)
{
	HandleError err;
	HandleSecurity sec(pContext->GetIdentity(), myself->GetIdentity());

	HTTPClient *client;
	Handle_t hndlClient = static_cast<Handle_t>(params[1]);
	if ((err=handlesys->ReadHandle(hndlClient, htHTTPClientObject, &sec, (void **)&client)) != HandleError_None)
	{
		return pContext->ThrowNativeError("Invalid HTTP client handle %x (error %d)", hndlClient, err);
	}

	char *endpoint;
	pContext->LocalToString(params[2], &endpoint);

	json_t *data;
	Handle_t hndlData = static_cast<Handle_t>(params[3]);
	if ((err=handlesys->ReadHandle(hndlData, htJSONObject, &sec, (void **)&data)) != HandleError_None)
	{
		return pContext->ThrowNativeError("Invalid data handle %x (error %d)", hndlData, err);
	}

	IPluginFunction *callback = pContext->GetFunctionById(params[4]);
	cell_t value = params[5];

	struct HTTPRequest request("PUT", endpoint, data);

	client->Request(request, callback, value);

	return 1;
}

static cell_t HTTPPatchRequest(IPluginContext *pContext, const cell_t *params)
{
	HandleError err;
	HandleSecurity sec(pContext->GetIdentity(), myself->GetIdentity());

	HTTPClient *client;
	Handle_t hndlClient = static_cast<Handle_t>(params[1]);
	if ((err=handlesys->ReadHandle(hndlClient, htHTTPClientObject, &sec, (void **)&client)) != HandleError_None)
	{
		return pContext->ThrowNativeError("Invalid HTTP client handle %x (error %d)", hndlClient, err);
	}

	char *endpoint;
	pContext->LocalToString(params[2], &endpoint);

	json_t *data;
	Handle_t hndlData = static_cast<Handle_t>(params[3]);
	if ((err=handlesys->ReadHandle(hndlData, htJSONObject, &sec, (void **)&data)) != HandleError_None)
	{
		return pContext->ThrowNativeError("Invalid data handle %x (error %d)", hndlData, err);
	}

	IPluginFunction *callback = pContext->GetFunctionById(params[4]);
	cell_t value = params[5];

	struct HTTPRequest request("PATCH", endpoint, data);

	client->Request(request, callback, value);

	return 1;
}

static cell_t HTTPDeleteRequest(IPluginContext *pContext, const cell_t *params)
{
	HandleError err;
	HandleSecurity sec(pContext->GetIdentity(), myself->GetIdentity());

	HTTPClient *client;
	Handle_t hndlClient = static_cast<Handle_t>(params[1]);
	if ((err=handlesys->ReadHandle(hndlClient, htHTTPClientObject, &sec, (void **)&client)) != HandleError_None)
	{
		return pContext->ThrowNativeError("Invalid HTTP client handle %x (error %d)", hndlClient, err);
	}

	char *endpoint;
	pContext->LocalToString(params[2], &endpoint);

	IPluginFunction *callback = pContext->GetFunctionById(params[3]);
	cell_t value = params[4];

	struct HTTPRequest request("DELETE", endpoint);

	client->Request(request, callback, value);

	return 1;
}

static cell_t GetHTTPResponseData(IPluginContext *pContext, const cell_t *params)
{
	HandleError err;
	HandleSecurity sec(pContext->GetIdentity(), myself->GetIdentity());

	struct HTTPResponse *response;
	Handle_t hndlResponse = static_cast<Handle_t>(params[1]);
	if ((err=handlesys->ReadHandle(hndlResponse, htHTTPResponseObject, &sec, (void **)&response)) != HandleError_None)
	{
		pContext->ThrowNativeError("Invalid HTTP response handle %x (error %d)", hndlResponse, err);
		return BAD_HANDLE;
	}

	if (response->data == NULL)
	{
		return BAD_HANDLE;
	}

	/* Return the same handle every time we get the HTTP response data */
	if (response->hndlData == BAD_HANDLE)
	{
		response->hndlData = handlesys->CreateHandleEx(htJSONObject, response->data, &sec, NULL, NULL);
		if (response->hndlData == BAD_HANDLE)
		{
			pContext->ThrowNativeError("Could not create data handle.");
			return BAD_HANDLE;
		}
	}

	return response->hndlData;
}

static cell_t GetHTTPResponseStatus(IPluginContext *pContext, const cell_t *params)
{
	HandleError err;
	HandleSecurity sec(pContext->GetIdentity(), myself->GetIdentity());

	struct HTTPResponse *response;
	Handle_t hndlResponse = static_cast<Handle_t>(params[1]);
	if ((err=handlesys->ReadHandle(hndlResponse, htHTTPResponseObject, &sec, (void **)&response)) != HandleError_None)
	{
		return pContext->ThrowNativeError("Invalid HTTP response handle %x (error %d)", hndlResponse, err);
	}

	return response->status;
}


const sp_nativeinfo_t curl_natives[] =
{
	{"HTTPClient.HTTPClient",			CreateHTTPClientObject},
	{"HTTPClient.Get",					HTTPGetRequest},
	{"HTTPClient.Post",					HTTPPostRequest},
	{"HTTPClient.Put",					HTTPPutRequest},
	{"HTTPClient.Patch",				HTTPPatchRequest},
	{"HTTPClient.Delete",				HTTPDeleteRequest},
	{"HTTPResponse.Data.get",			GetHTTPResponseData},
	{"HTTPResponse.Status.get",			GetHTTPResponseStatus},

	{NULL,								NULL}
};

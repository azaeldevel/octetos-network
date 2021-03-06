
/*
 * main.cc
 * Copyright (C) 2021 Azael Reyes <azael.devel@gmail.com>
 * 
 * nanoHttp is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * nanoHttp is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>

#include "http.hh"

static enum MHD_Result
answer_to_connection (void *cls, struct MHD_Connection *c,
                      const char *url, const char *method,
                      const char *version, const char *upload_data,
                      size_t *upload_data_size, void **con_cls)
{
	const char* page = "<html><body>Hello, browser librmicro 8...</body></html>";
  	octetos::http::Response response;
  	MHD_Result ret;
  	(void)cls;
  	(void)url;
  	(void)method;
  	(void)version;
  	(void)upload_data;
  	(void)upload_data_size;
  	(void)con_cls;

  	bool fl = response.from(strlen(page),(void*)page,MHD_RESPMEM_PERSISTENT);
	octetos::http::Connection connection(c);
  	ret = connection.response(MHD_HTTP_OK, response);

  	return ret;
}


int main (void)
{
  octetos::http::Service service(MHD_USE_AUTO | MHD_USE_INTERNAL_POLLING_THREAD, PORT, NULL, NULL, NULL);

  bool fl = service.start(answer_to_connection);
  if (not fl) return EXIT_FAILURE;

  	(void) getchar ();

  	service.stop();
  	return EXIT_SUCCESS;
}
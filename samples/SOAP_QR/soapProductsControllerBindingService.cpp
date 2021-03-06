/* soapProductsControllerBindingService.cpp
   Generated by gSOAP 2.8.8 from Products.h

Copyright(C) 2000-2012, Robert van Engelen, Genivia Inc. All Rights Reserved.
The generated code is released under one of the following licenses:
1) GPL or 2) Genivia's license for commercial use.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
*/

#include "soapProductsControllerBindingService.h"

ProductsControllerBindingService::ProductsControllerBindingService()
{	ProductsControllerBindingService_init(SOAP_IO_DEFAULT, SOAP_IO_DEFAULT);
}

ProductsControllerBindingService::ProductsControllerBindingService(const struct soap &_soap) : soap(_soap)
{ }

ProductsControllerBindingService::ProductsControllerBindingService(soap_mode iomode)
{	ProductsControllerBindingService_init(iomode, iomode);
}

ProductsControllerBindingService::ProductsControllerBindingService(soap_mode imode, soap_mode omode)
{	ProductsControllerBindingService_init(imode, omode);
}

ProductsControllerBindingService::~ProductsControllerBindingService()
{ }

void ProductsControllerBindingService::ProductsControllerBindingService_init(soap_mode imode, soap_mode omode)
{	soap_imode(this, imode);
	soap_omode(this, omode);
	static const struct Namespace namespaces[] =
{
	{"SOAP-ENV", "http://schemas.xmlsoap.org/soap/envelope/", "http://www.w3.org/*/soap-envelope", NULL},
	{"SOAP-ENC", "http://schemas.xmlsoap.org/soap/encoding/", "http://www.w3.org/*/soap-encoding", NULL},
	{"xsi", "http://www.w3.org/2001/XMLSchema-instance", "http://www.w3.org/*/XMLSchema-instance", NULL},
	{"xsd", "http://www.w3.org/2001/XMLSchema", "http://www.w3.org/*/XMLSchema", NULL},
	{"ns1", "urn:ProductsControllerwsdl", NULL, NULL},
	{NULL, NULL, NULL, NULL}
};
	soap_set_namespaces(this, namespaces);
};

void ProductsControllerBindingService::destroy()
{	soap_destroy(this);
	soap_end(this);
}

void ProductsControllerBindingService::reset()
{	destroy();
	soap_done(this);
	soap_init(this);
	ProductsControllerBindingService_init(SOAP_IO_DEFAULT, SOAP_IO_DEFAULT);
}

#ifndef WITH_PURE_VIRTUAL
ProductsControllerBindingService *ProductsControllerBindingService::copy()
{	ProductsControllerBindingService *dup = SOAP_NEW_COPY(ProductsControllerBindingService(*(struct soap*)this));
	return dup;
}
#endif

int ProductsControllerBindingService::soap_close_socket()
{	return soap_closesock(this);
}

int ProductsControllerBindingService::soap_force_close_socket()
{	return soap_force_closesock(this);
}

int ProductsControllerBindingService::soap_senderfault(const char *string, const char *detailXML)
{	return ::soap_sender_fault(this, string, detailXML);
}

int ProductsControllerBindingService::soap_senderfault(const char *subcodeQName, const char *string, const char *detailXML)
{	return ::soap_sender_fault_subcode(this, subcodeQName, string, detailXML);
}

int ProductsControllerBindingService::soap_receiverfault(const char *string, const char *detailXML)
{	return ::soap_receiver_fault(this, string, detailXML);
}

int ProductsControllerBindingService::soap_receiverfault(const char *subcodeQName, const char *string, const char *detailXML)
{	return ::soap_receiver_fault_subcode(this, subcodeQName, string, detailXML);
}

void ProductsControllerBindingService::soap_print_fault(FILE *fd)
{	::soap_print_fault(this, fd);
}

#ifndef WITH_LEAN
#ifndef WITH_COMPAT
void ProductsControllerBindingService::soap_stream_fault(std::ostream& os)
{	::soap_stream_fault(this, os);
}
#endif

char *ProductsControllerBindingService::soap_sprint_fault(char *buf, size_t len)
{	return ::soap_sprint_fault(this, buf, len);
}
#endif

void ProductsControllerBindingService::soap_noheader()
{	this->header = NULL;
}

const SOAP_ENV__Header *ProductsControllerBindingService::soap_header()
{	return this->header;
}

int ProductsControllerBindingService::run(int port)
{	if (soap_valid_socket(bind(NULL, port, 100)))
	{	for (;;)
		{	if (!soap_valid_socket(accept()) || serve())
				return this->error;
			soap_destroy(this);
			soap_end(this);
		}
	}
	else
		return this->error;
	return SOAP_OK;
}

SOAP_SOCKET ProductsControllerBindingService::bind(const char *host, int port, int backlog)
{	return soap_bind(this, host, port, backlog);
}

SOAP_SOCKET ProductsControllerBindingService::accept()
{	return soap_accept(this);
}

int ProductsControllerBindingService::serve()
{
#ifndef WITH_FASTCGI
	unsigned int k = this->max_keep_alive;
#endif
	do
	{

#ifndef WITH_FASTCGI
		if (this->max_keep_alive > 0 && !--k)
			this->keep_alive = 0;
#endif

		if (soap_begin_serve(this))
		{	if (this->error >= SOAP_STOP)
				continue;
			return this->error;
		}
		if (dispatch() || (this->fserveloop && this->fserveloop(this)))
		{
#ifdef WITH_FASTCGI
			soap_send_fault(this);
#else
			return soap_send_fault(this);
#endif
		}

#ifdef WITH_FASTCGI
		soap_destroy(this);
		soap_end(this);
	} while (1);
#else
	} while (this->keep_alive);
#endif
	return SOAP_OK;
}

static int serve_ns1__getProduct(ProductsControllerBindingService*);
static int serve_ns1__getImagesData(ProductsControllerBindingService*);

int ProductsControllerBindingService::dispatch()
{	soap_peek_element(this);
	if (!soap_match_tag(this, this->tag, "ns1:getProduct"))
		return serve_ns1__getProduct(this);
	if (!soap_match_tag(this, this->tag, "ns1:getImagesData"))
		return serve_ns1__getImagesData(this);
	return this->error = SOAP_NO_METHOD;
}

static int serve_ns1__getProduct(ProductsControllerBindingService *soap)
{	struct ns1__getProduct soap_tmp_ns1__getProduct;
	struct ns1__getProductResponse _param_1;
	soap_default_ns1__getProductResponse(soap, &_param_1);
	soap_default_ns1__getProduct(soap, &soap_tmp_ns1__getProduct);
	soap->encodingStyle = "http://schemas.xmlsoap.org/soap/encoding/";
	if (!soap_get_ns1__getProduct(soap, &soap_tmp_ns1__getProduct, "ns1:getProduct", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = soap->getProduct(soap_tmp_ns1__getProduct.companyID, soap_tmp_ns1__getProduct.userMD5, soap_tmp_ns1__getProduct.product, _param_1);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	soap_serialize_ns1__getProductResponse(soap, &_param_1);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns1__getProductResponse(soap, &_param_1, "ns1:getProductResponse", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns1__getProductResponse(soap, &_param_1, "ns1:getProductResponse", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

static int serve_ns1__getImagesData(ProductsControllerBindingService *soap)
{	struct ns1__getImagesData soap_tmp_ns1__getImagesData;
	struct ns1__getImagesDataResponse _param_2;
	soap_default_ns1__getImagesDataResponse(soap, &_param_2);
	soap_default_ns1__getImagesData(soap, &soap_tmp_ns1__getImagesData);
	soap->encodingStyle = "http://schemas.xmlsoap.org/soap/encoding/";
	if (!soap_get_ns1__getImagesData(soap, &soap_tmp_ns1__getImagesData, "ns1:getImagesData", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = soap->getImagesData(soap_tmp_ns1__getImagesData.companyID, soap_tmp_ns1__getImagesData.userMD5, soap_tmp_ns1__getImagesData.product, _param_2);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	soap_serialize_ns1__getImagesDataResponse(soap, &_param_2);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns1__getImagesDataResponse(soap, &_param_2, "ns1:getImagesDataResponse", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns1__getImagesDataResponse(soap, &_param_2, "ns1:getImagesDataResponse", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}
/* End of server object code */

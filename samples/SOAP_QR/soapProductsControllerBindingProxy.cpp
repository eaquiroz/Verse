/* soapProductsControllerBindingProxy.cpp
   Generated by gSOAP 2.8.8 from Products.h

Copyright(C) 2000-2012, Robert van Engelen, Genivia Inc. All Rights Reserved.
The generated code is released under one of the following licenses:
1) GPL or 2) Genivia's license for commercial use.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
*/

#include "soapProductsControllerBindingProxy.h"

ProductsControllerBindingProxy::ProductsControllerBindingProxy()
{	ProductsControllerBindingProxy_init(SOAP_IO_DEFAULT, SOAP_IO_DEFAULT);
}

ProductsControllerBindingProxy::ProductsControllerBindingProxy(const struct soap &_soap) : soap(_soap)
{ }

ProductsControllerBindingProxy::ProductsControllerBindingProxy(const char *url)
{	ProductsControllerBindingProxy_init(SOAP_IO_DEFAULT, SOAP_IO_DEFAULT);
	soap_endpoint = url;
}

ProductsControllerBindingProxy::ProductsControllerBindingProxy(soap_mode iomode)
{	ProductsControllerBindingProxy_init(iomode, iomode);
}

ProductsControllerBindingProxy::ProductsControllerBindingProxy(const char *url, soap_mode iomode)
{	ProductsControllerBindingProxy_init(iomode, iomode);
	soap_endpoint = url;
}

ProductsControllerBindingProxy::ProductsControllerBindingProxy(soap_mode imode, soap_mode omode)
{	ProductsControllerBindingProxy_init(imode, omode);
}

ProductsControllerBindingProxy::~ProductsControllerBindingProxy()
{ }

void ProductsControllerBindingProxy::ProductsControllerBindingProxy_init(soap_mode imode, soap_mode omode)
{	soap_imode(this, imode);
	soap_omode(this, omode);
	soap_endpoint = NULL;
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
}

void ProductsControllerBindingProxy::destroy()
{	soap_destroy(this);
	soap_end(this);
}

void ProductsControllerBindingProxy::reset()
{	destroy();
	soap_done(this);
	soap_init(this);
	ProductsControllerBindingProxy_init(SOAP_IO_DEFAULT, SOAP_IO_DEFAULT);
}

void ProductsControllerBindingProxy::soap_noheader()
{	this->header = NULL;
}

const SOAP_ENV__Header *ProductsControllerBindingProxy::soap_header()
{	return this->header;
}

const SOAP_ENV__Fault *ProductsControllerBindingProxy::soap_fault()
{	return this->fault;
}

const char *ProductsControllerBindingProxy::soap_fault_string()
{	return *soap_faultstring(this);
}

const char *ProductsControllerBindingProxy::soap_fault_detail()
{	return *soap_faultdetail(this);
}

int ProductsControllerBindingProxy::soap_close_socket()
{	return soap_closesock(this);
}

int ProductsControllerBindingProxy::soap_force_close_socket()
{	return soap_force_closesock(this);
}

void ProductsControllerBindingProxy::soap_print_fault(FILE *fd)
{	::soap_print_fault(this, fd);
}

#ifndef WITH_LEAN
#ifndef WITH_COMPAT
void ProductsControllerBindingProxy::soap_stream_fault(std::ostream& os)
{	::soap_stream_fault(this, os);
}
#endif

char *ProductsControllerBindingProxy::soap_sprint_fault(char *buf, size_t len)
{	return ::soap_sprint_fault(this, buf, len);
}
#endif

int ProductsControllerBindingProxy::getProduct(const char *endpoint, const char *soap_action, int companyID, std::string userMD5, std::string product, struct ns1__getProductResponse &_param_1)
{	struct soap *soap = this;
	struct ns1__getProduct soap_tmp_ns1__getProduct;
	if (endpoint)
		soap_endpoint = endpoint;
	if (!soap_endpoint)
		soap_endpoint = "http://localhost:8888/VerseCMS/index.php?r=Products/products/wsdl&ws=1";
	if (!soap_action)
		soap_action = "urn:ProductsControllerwsdl#getProduct";
	soap->encodingStyle = "http://schemas.xmlsoap.org/soap/encoding/";
	soap_tmp_ns1__getProduct.companyID = companyID;
	soap_tmp_ns1__getProduct.userMD5 = userMD5;
	soap_tmp_ns1__getProduct.product = product;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns1__getProduct(soap, &soap_tmp_ns1__getProduct);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns1__getProduct(soap, &soap_tmp_ns1__getProduct, "ns1:getProduct", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns1__getProduct(soap, &soap_tmp_ns1__getProduct, "ns1:getProduct", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&_param_1)
		return soap_closesock(soap);
	soap_default_ns1__getProductResponse(soap, &_param_1);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_get_ns1__getProductResponse(soap, &_param_1, "", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int ProductsControllerBindingProxy::getImagesData(const char *endpoint, const char *soap_action, int companyID, std::string userMD5, std::string product, struct ns1__getImagesDataResponse &_param_2)
{	struct soap *soap = this;
	struct ns1__getImagesData soap_tmp_ns1__getImagesData;
	if (endpoint)
		soap_endpoint = endpoint;
	if (!soap_endpoint)
		soap_endpoint = "http://localhost:8888/VerseCMS/index.php?r=Products/products/wsdl&ws=1";
	if (!soap_action)
		soap_action = "urn:ProductsControllerwsdl#getImagesData";
	soap->encodingStyle = "http://schemas.xmlsoap.org/soap/encoding/";
	soap_tmp_ns1__getImagesData.companyID = companyID;
	soap_tmp_ns1__getImagesData.userMD5 = userMD5;
	soap_tmp_ns1__getImagesData.product = product;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns1__getImagesData(soap, &soap_tmp_ns1__getImagesData);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns1__getImagesData(soap, &soap_tmp_ns1__getImagesData, "ns1:getImagesData", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns1__getImagesData(soap, &soap_tmp_ns1__getImagesData, "ns1:getImagesData", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&_param_2)
		return soap_closesock(soap);
	soap_default_ns1__getImagesDataResponse(soap, &_param_2);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_get_ns1__getImagesDataResponse(soap, &_param_2, "", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}
/* End of client proxy code */
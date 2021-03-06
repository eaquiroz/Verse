/* Products.h
   Generated by wsdl2h 2.8.8 from http://localhost:8888/VerseCMS/index.php?r=Products/products/wsdl and typemap.dat
   2012-04-11 20:19:58 GMT

   DO NOT INCLUDE THIS FILE DIRECTLY INTO YOUR PROJECT BUILDS
   USE THE soapcpp2-GENERATED SOURCE CODE FILES FOR YOUR PROJECT BUILDS

   gSOAP XML Web services tools.
   Copyright (C) 2001-2012 Robert van Engelen, Genivia Inc. All Rights Reserved.
   Part of this software is released under one of the following licenses:
   GPL or Genivia's license for commercial use.
*/

/** @page page_notes Usage Notes

NOTE:

 - Run soapcpp2 on Products.h to generate the SOAP/XML processing logic.
   Use soapcpp2 option -I to specify paths for #import
   To build with STL, 'stlvector.h' is imported from 'import' dir in package.
   Use soapcpp2 option -i to generate improved proxy and server classes.
 - Use wsdl2h options -c and -s to generate pure C code or C++ code without STL.
 - Use 'typemap.dat' to control namespace bindings and type mappings.
   It is strongly recommended to customize the names of the namespace prefixes
   generated by wsdl2h. To do so, modify the prefix bindings in the Namespaces
   section below and add the modified lines to 'typemap.dat' to rerun wsdl2h.
 - Use Doxygen (www.doxygen.org) on this file to generate documentation.
 - Use wsdl2h options -nname and -Nname to globally rename the prefix 'ns'.
 - Use wsdl2h option -d to enable DOM support for xsd:anyType.
 - Use wsdl2h option -g to auto-generate readers and writers for root elements.
 - Struct/class members serialized as XML attributes are annotated with a '@'.
 - Struct/class members that have a special role are annotated with a '$'.

WARNING:

   DO NOT INCLUDE THIS FILE DIRECTLY INTO YOUR PROJECT BUILDS.
   USE THE SOURCE CODE FILES GENERATED BY soapcpp2 FOR YOUR PROJECT BUILDS:
   THE soapStub.h FILE CONTAINS THIS CONTENT WITHOUT ANNOTATIONS.

LICENSE:

@verbatim
--------------------------------------------------------------------------------
gSOAP XML Web services tools
Copyright (C) 2000-2012, Robert van Engelen, Genivia Inc. All Rights Reserved.

This software is released under one of the following two licenses:
1) GPL or 2) Genivia's license for commercial use.
--------------------------------------------------------------------------------
1) GPL license.

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place, Suite 330, Boston, MA 02111-1307 USA

Author contact information:
engelen@genivia.com / engelen@acm.org

This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
--------------------------------------------------------------------------------
2) A commercial-use license is available from Genivia, Inc., contact@genivia.com
--------------------------------------------------------------------------------
@endverbatim

*/


//gsoapopt w

/******************************************************************************\
 *                                                                            *
 * Definitions                                                                *
 *   urn:ProductsControllerwsdl                                               *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Import                                                                     *
 *                                                                            *
\******************************************************************************/


// STL vector containers (use option -s to remove STL dependency)
#import "stlvector.h"

/******************************************************************************\
 *                                                                            *
 * Schema Namespaces                                                          *
 *                                                                            *
\******************************************************************************/


/* NOTE:

It is strongly recommended to customize the names of the namespace prefixes
generated by wsdl2h. To do so, modify the prefix bindings below and add the
modified lines to typemap.dat to rerun wsdl2h:

ns1 = "urn:ProductsControllerwsdl"

*/

#define SOAP_NAMESPACE_OF_ns1	"urn:ProductsControllerwsdl"
//gsoap ns1   schema namespace:	urn:ProductsControllerwsdl
//gsoap ns1   schema form:	unqualified

/******************************************************************************\
 *                                                                            *
 * Built-in Schema Types and Top-Level Elements and Attributes                *
 *                                                                            *
\******************************************************************************/


/// Primitive built-in type "xs:integer"
typedef std::string xsd__integer;

/******************************************************************************\
 *                                                                            *
 * Forward Declarations                                                       *
 *                                                                            *
\******************************************************************************/



//  Forward declaration of class ns1__Products.
class ns1__Products;

//  Forward declaration of class ProductImagesArray.
class ProductImagesArray;

//  Forward declaration of class ns1__ProductImages.
class ns1__ProductImages;

/******************************************************************************\
 *                                                                            *
 * Schema Types and Top-Level Elements and Attributes                         *
 *   urn:ProductsControllerwsdl                                               *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Schema Complex Types and Top-Level Elements                                *
 *   urn:ProductsControllerwsdl                                               *
 *                                                                            *
\******************************************************************************/


/// "urn:ProductsControllerwsdl":Products is a complexType.
class ns1__Products
{ public:
/// Element idProducts of type xs:integer.
    xsd__integer                         idProducts                     1;	///< Required element.
/// Element name of type xs:string.
    std::string                          name                           1;	///< Required element.
/// Element price of type xs:float.
    float                                price                          1;	///< Required element.
/// Element ref of type xs:string.
    std::string                          ref                            1;	///< Required element.
/// Element description of type xs:string.
    std::string                          description                    1;	///< Required element.
/// Element idMarker of type xs:int.
    int                                  idMarker                       1;	///< Required element.
/// Element model3d of type xs:string.
    std::string                          model3d                        1;	///< Required element.
/// A handle to the soap struct that manages this instance (automatically set)
    struct soap                         *soap                          ;
};

/// "urn:ProductsControllerwsdl":ProductImages is a complexType.
class ns1__ProductImages
{ public:
/// Element idProductImage of type xs:integer.
    xsd__integer                         idProductImage                 1;	///< Required element.
/// Element url of type xs:string.
    std::string                          url                            1;	///< Required element.
/// Element altName of type xs:string.
    std::string                          altName                        1;	///< Required element.
/// Element idProduct of type xs:integer.
    xsd__integer                         idProduct                      1;	///< Required element.
/// Element owner of type xs:integer.
    xsd__integer                         owner                          1;	///< Required element.
/// A handle to the soap struct that manages this instance (automatically set)
    struct soap                         *soap                          ;
};

/// "urn:ProductsControllerwsdl":ProductImagesArray is a complexType with complexContent restriction of SOAP-ENC:Array.
/// SOAP encoded array of "urn:ProductsControllerwsdl":ProductImages
class ProductImagesArray
{ public:
/// Pointer to array of ns1__ProductImages*.
    ns1__ProductImages*                 *__ptr                         ;
/// Size of the dynamic array.
    int                                  __size                        ;
/// Offset for partially transmitted arrays (uncomment only when required).
//  int                                  __offset                      ;
/// A handle to the soap struct that manages this instance (automatically set)
    struct soap                         *soap                          ;
};

/******************************************************************************\
 *                                                                            *
 * Additional Top-Level Elements                                              *
 *   urn:ProductsControllerwsdl                                               *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Additional Top-Level Attributes                                            *
 *   urn:ProductsControllerwsdl                                               *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Services                                                                   *
 *                                                                            *
\******************************************************************************/


//gsoap ns1  service name:	ProductsControllerBinding 
//gsoap ns1  service type:	ProductsControllerPortType 
//gsoap ns1  service port:	http://localhost:8888/VerseCMS/index.php?r=Products/products/wsdl&ws=1 
//gsoap ns1  service namespace:	urn:ProductsControllerwsdl 
//gsoap ns1  service transport:	http://schemas.xmlsoap.org/soap/http 

/** @mainpage ProductsController Definitions

@section ProductsController_bindings Service Bindings

  - @ref ProductsControllerBinding

@section ProductsController_more More Information

  - @ref page_notes "Usage Notes"

  - @ref page_XMLDataBinding "XML Data Binding"

  - @ref SOAP_ENV__Header "SOAP Header Content" (when applicable)

  - @ref SOAP_ENV__Detail "SOAP Fault Detail Content" (when applicable)


*/

/**

@page ProductsControllerBinding Binding "ProductsControllerBinding"

@section ProductsControllerBinding_operations Operations of Binding  "ProductsControllerBinding"

  - @ref ns1__getProduct

  - @ref ns1__getImagesData

@section ProductsControllerBinding_ports Endpoints of Binding  "ProductsControllerBinding"

  - http://localhost:8888/VerseCMS/index.php?r=Products/products/wsdl&ws=1

Note: use wsdl2h option -N to change the service binding prefix name

*/

/******************************************************************************\
 *                                                                            *
 * Service Binding                                                            *
 *   ProductsControllerBinding                                                *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Service Operation                                                          *
 *   ns1__getProduct                                                          *
 *                                                                            *
\******************************************************************************/

/// Operation response struct "ns1__getProductResponse" of service binding "ProductsControllerBinding" operation "ns1__getProduct"
struct ns1__getProductResponse
{
    ns1__Products*                      return_;
};

/// Operation "ns1__getProduct" of service binding "ProductsControllerBinding"

/**

Operation details:


  - SOAP RPC encodingStyle="http://schemas.xmlsoap.org/soap/encoding/"

  - SOAP action: "urn:ProductsControllerwsdl#getProduct"

  - Addressing action: "urn:ProductsControllerwsdl/ProductsControllerPortType/getProduct"

  - Addressing response action: "urn:ProductsControllerwsdl/ProductsControllerPortType/getProductResponse"

C stub function (defined in soapClient.c[pp] generated by soapcpp2):
@code
  int soap_call_ns1__getProduct(
    struct soap *soap,
    NULL, // char *endpoint = NULL selects default endpoint for this operation
    NULL, // char *action = NULL selects default action for this operation
    // request parameters:
    int                                 companyID,
    std::string                         userMD5,
    std::string                         product,
    // response parameters:
    struct ns1__getProductResponse&
  );
@endcode

C server function (called from the service dispatcher defined in soapServer.c[pp]):
@code
  int ns1__getProduct(
    struct soap *soap,
    // request parameters:
    int                                 companyID,
    std::string                         userMD5,
    std::string                         product,
    // response parameters:
    struct ns1__getProductResponse&
  );
@endcode

C++ proxy class (defined in soapProductsControllerBindingProxy.h):
@code
  class ProductsControllerBindingProxy;
@endcode
Important: use soapcpp2 option '-i' to generate greatly improved and easy-to-use proxy classes;

C++ service class (defined in soapProductsControllerBindingService.h):
@code
  class ProductsControllerBindingService;
@endcode
Important: use soapcpp2 option '-i' to generate greatly improved and easy-to-use service classes;

*/

//gsoap ns1  service method-style:	getProduct rpc
//gsoap ns1  service method-encoding:	getProduct http://schemas.xmlsoap.org/soap/encoding/
//gsoap ns1  service method-action:	getProduct urn:ProductsControllerwsdl#getProduct
//gsoap ns1  service method-output-action:	getProduct urn:ProductsControllerwsdl/ProductsControllerPortType/getProductResponse
int ns1__getProduct(
    int                                 companyID,	///< Request parameter
    std::string                         userMD5,	///< Request parameter
    std::string                         product,	///< Request parameter
    struct ns1__getProductResponse     &	///< Response struct parameter
);

/******************************************************************************\
 *                                                                            *
 * Service Operation                                                          *
 *   ns1__getImagesData                                                       *
 *                                                                            *
\******************************************************************************/

/// Operation response struct "ns1__getImagesDataResponse" of service binding "ProductsControllerBinding" operation "ns1__getImagesData"
struct ns1__getImagesDataResponse
{
    ProductImagesArray*                 return_;
};

/// Operation "ns1__getImagesData" of service binding "ProductsControllerBinding"

/**

Operation details:


  - SOAP RPC encodingStyle="http://schemas.xmlsoap.org/soap/encoding/"

  - SOAP action: "urn:ProductsControllerwsdl#getImagesData"

  - Addressing action: "urn:ProductsControllerwsdl/ProductsControllerPortType/getImagesData"

  - Addressing response action: "urn:ProductsControllerwsdl/ProductsControllerPortType/getImagesDataResponse"

C stub function (defined in soapClient.c[pp] generated by soapcpp2):
@code
  int soap_call_ns1__getImagesData(
    struct soap *soap,
    NULL, // char *endpoint = NULL selects default endpoint for this operation
    NULL, // char *action = NULL selects default action for this operation
    // request parameters:
    int                                 companyID,
    std::string                         userMD5,
    std::string                         product,
    // response parameters:
    struct ns1__getImagesDataResponse&
  );
@endcode

C server function (called from the service dispatcher defined in soapServer.c[pp]):
@code
  int ns1__getImagesData(
    struct soap *soap,
    // request parameters:
    int                                 companyID,
    std::string                         userMD5,
    std::string                         product,
    // response parameters:
    struct ns1__getImagesDataResponse&
  );
@endcode

C++ proxy class (defined in soapProductsControllerBindingProxy.h):
@code
  class ProductsControllerBindingProxy;
@endcode
Important: use soapcpp2 option '-i' to generate greatly improved and easy-to-use proxy classes;

C++ service class (defined in soapProductsControllerBindingService.h):
@code
  class ProductsControllerBindingService;
@endcode
Important: use soapcpp2 option '-i' to generate greatly improved and easy-to-use service classes;

*/

//gsoap ns1  service method-style:	getImagesData rpc
//gsoap ns1  service method-encoding:	getImagesData http://schemas.xmlsoap.org/soap/encoding/
//gsoap ns1  service method-action:	getImagesData urn:ProductsControllerwsdl#getImagesData
//gsoap ns1  service method-output-action:	getImagesData urn:ProductsControllerwsdl/ProductsControllerPortType/getImagesDataResponse
int ns1__getImagesData(
    int                                 companyID,	///< Request parameter
    std::string                         userMD5,	///< Request parameter
    std::string                         product,	///< Request parameter
    struct ns1__getImagesDataResponse  &	///< Response struct parameter
);

/******************************************************************************\
 *                                                                            *
 * XML Data Binding                                                           *
 *                                                                            *
\******************************************************************************/


/**

@page page_XMLDataBinding XML Data Binding

SOAP/XML services use data bindings contractually bound by WSDL and auto-
generated by wsdl2h and soapcpp2 (see Service Bindings). Plain data bindings
are adopted from XML schemas as part of the WSDL types section or when running
wsdl2h on a set of schemas to produce non-SOAP-based XML data bindings.

The following readers and writers are C/C++ data type (de)serializers auto-
generated by wsdl2h and soapcpp2. Run soapcpp2 on this file to generate the
(de)serialization code, which is stored in soapC.c[pp]. Include "soapH.h" in
your code to import these data type and function declarations. Only use the
soapcpp2-generated files in your project build. Do not include the wsdl2h-
generated .h file in your code.

XML content can be retrieved from:
  - a file descriptor, using soap->recvfd = fd
  - a socket, using soap->socket = ...
  - a C++ stream, using soap->is = ...
  - a buffer, using the soap->frecv() callback

XML content can be stored to:
  - a file descriptor, using soap->sendfd = fd
  - a socket, using soap->socket = ...
  - a C++ stream, using soap->os = ...
  - a buffer, using the soap->fsend() callback


@section ns1 Top-level root elements of schema "urn:ProductsControllerwsdl"

*/

/* End of Products.h */

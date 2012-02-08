/**
 * @file QR.cpp
 * @author  David Millan <david.millan@damiles.com>
 * @version 0.1
 *
 * @section LICENSE
 *
 * Copyright © 2011, Augmate Corporation LLC.
 * This file is part of VERSE.
 * 
 * VERSE is free software: you can redistribute it and/or 
 * modify it under the terms of the GNU General Public License 
 * as published by the Free Software Foundation, either version 3 
 * of the License, or (at your option) any later version.
 * 
 * VERSE is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty 
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License 
 * along with VERSE. If not, see <http://www.gnu.org/licenses/>.
 *
 * @section DESCRIPTION
 *
 * QR decode image.
 */


#include "QR.h"

namespace AR {

QR::QR(){
	//CReate decoder
	decoder=qr_decoder_open();
	//Init buffer with one image
	
	START=1;
	
	text_size=0;
	text=NULL;
}

void QR::process(IplImage* img) {
	
	if(START)
	{
		src=cvCloneImage(img);
		qr_decoder_set_image_buffer(decoder,src);
		START=0;
	}else{

		cvCopy(img,src);

		 if(!qr_decoder_is_busy(decoder)){
			//
		    // if left-bottom origin (MS-Windows style) format,
		    // it must be converted to left-top origin.
		    //
		    //if(frame->origin)
		    //    cvConvertImage(frame,src,CV_CVTIMG_FLIP);
		    //else
		    //    cvCopy(frame,src);

		    //
		    // While decoding is a failure, decrease the
		    // adaptive_th_size parameter.
		    // Note that the adaptive_th_size must be odd.
		    //
		    short sz,stat;
		    for(sz=25,stat=0;
		        (sz>=3)&&((stat&QR_IMAGEREADER_DECODED)==0);
		        sz-=2)
		        stat=qr_decoder_decode(decoder,sz);

		    //
		    // on suceed decoding, print decoded text.
		    //
		    QrCodeHeader header;
		    if(qr_decoder_get_header(decoder,&header)){
		        if(text_size<header.byte_size+1){
		            if(text)
		                delete text;
		            
		            text_size=header.byte_size+1;
		            text=new unsigned char[text_size];
		        }
		        qr_decoder_get_body(decoder,text,text_size);
		    }
		}
	}

}

}

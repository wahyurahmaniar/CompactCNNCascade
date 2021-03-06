/*
*	Copyright (c) 2018, Ilya Kalinovskiy
*	All rights reserved.
*
*	This is an implementation of the algorithm described in the following paper:
*		I.A. Kalinovskiy, V.G. Spitsyn,
*		Compact Convolutional Neural Network Cascade for Face Detection,
*		http://arxiv.org/abs/1508.01292.
*
*	Redistribution and use of this program as source code or in binary form, with or without modifications, are permitted provided that the following conditions are met:
*		1. Redistributions may not be sold, nor may they be used in a commercial product or activity without prior permission from the copyright holder (contact him at kua_21@mail.ru).
*		2. Redistributions may not be used for military purposes.
*		3. Any published work which utilizes this program shall include the reference to the paper available at http://arxiv.org/abs/1508.01292
*		4. Redistributions must retain the above copyright notice and the reference to the algorithm on which the implementation is based on, this list of conditions and the following disclaimer.
*
*	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
*	IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/


#pragma once

#include "config.h"
#include "image.h"

#if defined(USE_SSE) || defined(USE_AVX)
#	include <immintrin.h>
#endif


//================================================================================================================================================


namespace NeuralNetworksLib
{
	namespace SIMD
	{
		class ImageConverter
		{
		private:
			static inline void Img8uToImg32f(Image_32f& img_32f, Image_8u& img_8u, int num_threads = 1);
			static inline void Img8uBGRToImg32fGRAY(Image_32f& img_32f, Image_8u& img_8u, int num_threads = 1);
			static inline void Img8uBGRAToImg32fGRAY(Image_32f& img_32f, Image_8u& img_8u, int num_threads = 1);

		public:
			static int Img8uToImg32fGRAY(Image_32f& img_32f, Image_8u& img_8u, int num_threads = 1);
			static int Img8uToImg32fGRAY_blur(Image_32f& img_32f, Image_8u& img_8u, const float* kernel_col, const float* kernel_row, int num_threads = 1);

			static void FloatToUChar(Image_8u& dst, Image_32f& src, const Rect& roi);

			static void UCharToFloat(Image_32f& dst, Image_8u& src, int offset = 0);
			static void UCharToFloat_inv(Image_32f& dst, Image_8u& src);
			static void UCharToFloat_add_rnd(Image_32f& dst, Image_8u& src, TmpImage<char>& rnd_matrix, int offset = 0);
		};

		void colFilter3_32f(Image_32f& dst, Image_32f& src, const float* kernel, int num_threads = 1);
		void rowFilter3_32f(Image_32f& dst, Image_32f& src, const float* kernel, int num_threads = 1);

		void equalizeImage(Image_8u& img);
	}
}
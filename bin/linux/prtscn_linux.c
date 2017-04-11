#include <stdio.h>
#include <stdlib.h>
#include <X11/X.h>
#include <X11/Xutil.h>
#include "prtscn_linux.h"
#include "png.h"

static int save_png_to_file (XImage * image, const char* path)
{
	FILE * fp;
	png_structp png_ptr = NULL;
	png_infop info_ptr = NULL;
	int x, y;
	png_byte ** row_pointers = NULL;


	int status = -1;

	int pixel_size = 3;
	int depth = 8;

	fp = fopen (path, "wb");
	if (! fp) {
		goto fopen_failed;
	}

	png_ptr = png_create_write_struct (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (png_ptr == NULL) {
		goto png_create_write_struct_failed;
	}

	info_ptr = png_create_info_struct (png_ptr);
	if (info_ptr == NULL) {
		goto png_create_info_struct_failed;
	}

	/* Set image attributes. */

	png_set_IHDR (png_ptr,
				  info_ptr,
				  image->width,
				  image->height,
				  depth,
				  PNG_COLOR_TYPE_RGB,
				  PNG_INTERLACE_NONE,
				  PNG_COMPRESSION_TYPE_DEFAULT,
				  PNG_FILTER_TYPE_DEFAULT);

	/* Initialize rows of PNG. */
	unsigned long red_mask   = image->red_mask;
	unsigned long green_mask = image->green_mask;
	unsigned long blue_mask  = image->blue_mask;
	row_pointers = png_malloc (png_ptr, image->height * sizeof (png_byte *));
	for (y = 0; y < image->height; y++) {
		png_byte *row = png_malloc (png_ptr, image->width * pixel_size);
		row_pointers[y] = row;
		for (x = 0; x < image->width; x++) {
			unsigned long pixel = XGetPixel(image,x,y);
			*row++ = (pixel & red_mask) >> 16;
			*row++ = (pixel & green_mask) >> 8;
			*row++ = (pixel & blue_mask);
		}
	}

	/* Write the image data to "fp". */

	png_init_io (png_ptr, fp);
	png_set_rows (png_ptr, info_ptr, row_pointers);
	png_write_png (png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);

	/* The routine has successfully written the file, so we set
	"status" to a value which indicates success. */

	status = 0;

	for (y = 0; y < image->height; y++) {
		png_free (png_ptr, row_pointers[y]);
	}
	png_free (png_ptr, row_pointers);

	png_create_info_struct_failed:
		png_destroy_write_struct (&png_ptr, &info_ptr);
	png_create_write_struct_failed:
		fclose (fp);
	fopen_failed:
		return status;
}


void getScreen(const int xx,const int yy, int W, int H, const char* path)
{
	Display *display = XOpenDisplay(NULL);
	Window root = DefaultRootWindow(display);

	if (W == 0) {
		W = XWidthOfScreen(XDefaultScreenOfDisplay(display));
	}
	if (H == 0) {
		H = XHeightOfScreen(XDefaultScreenOfDisplay(display));
	}

	XImage *image = XGetImage(display,root, xx,yy, W,H, AllPlanes, ZPixmap);

	save_png_to_file(image, path);
	XDestroyImage(image);
	XDestroyWindow(display, root);
	XCloseDisplay(display);
}

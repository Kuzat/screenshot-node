#include <ApplicationServices/ApplicationServices.h>
#include <CoreGraphics/CoreGraphics.h>
#include <CoreServices/CoreServices.h>
#include <ImageIO/ImageIO.h>
#include <Foundation/Foundation.h>
#include "prtscn_osx.h"

int CGImageWriteToFile(CGImageRef image, NSString *path) {
	CFURLRef url = (__bridge CFURLRef)[NSURL fileURLWithPath:path];
	CGImageDestinationRef destination = CGImageDestinationCreateWithURL(url, kUTTypePNG, 1, NULL);
	if (!destination) {
		NSLog(@"Failed to create CGImageDestination for %@", path);
		return 1;
	}

	CGImageDestinationAddImage(destination, image, nil);

	if (!CGImageDestinationFinalize(destination)) {
		NSLog(@"Failed to write image to %@", path);
		CFRelease(destination);
		return 1;
	}

	CFRelease(destination);
	return 0;
}

void getScreen(const int x, const int y, int W, int H, const char* path) {
	if (W == 0) {
		W = (int) CGDisplayPixelsWide(CGMainDisplayID());
	}
	if (H == 0) {
		H = (int) CGDisplayPixelsHigh(CGMainDisplayID());
	}
	CGRect rect = CGRectMake(x, y, W, H);
	CGImageRef image_ref = CGDisplayCreateImageForRect(CGMainDisplayID(), rect);
	CGImageWriteToFile(image_ref, [NSString stringWithUTF8String:path]);
	CGImageRelease(image_ref);
}

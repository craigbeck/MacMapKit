//
//  MKMapView.h
//  MapKit
//
//  Created by Rick Fillion on 7/11/10.
//  Copyright 2010 Centrix.ca. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <WebKit/WebKit.h>
#import <CoreLocation/CoreLocation.h>
#import <MapKit/MKTypes.h>
#import <MapKit/MKGeometry.h>
#import <MapKit/MKOverlay.h>

@protocol MKMapViewDelegate;
@class MKUserLocation;
@class MKOverlayView;

@interface MKMapView : NSView <CLLocationManagerDelegate> {    
    id <MKMapViewDelegate> delegate;
    MKMapType mapType;
    MKUserLocation *userLocation;
    BOOL showsUserLocation;
    NSMutableArray *overlays;
    
@private
    WebView *webView;
    CLLocationManager *locationManager;
    BOOL hasSetCenterCoordinate;
    // Overlays
    CFMutableDictionaryRef overlayViews;
    CFMutableDictionaryRef overlayScriptObjects;

    
}
@property (nonatomic, assign) id <MKMapViewDelegate> delegate;

@property(nonatomic) MKMapType mapType;

@property(nonatomic) MKCoordinateRegion region;
@property(nonatomic) CLLocationCoordinate2D centerCoordinate;
@property(nonatomic) BOOL showsUserLocation;
@property(nonatomic, getter=isScrollEnabled) BOOL scrollEnabled;
@property(nonatomic, getter=isZoomEnabled) BOOL zoomEnabled;
@property(nonatomic, readonly, getter=isUserLocationVisible) BOOL userLocationVisible;
@property(nonatomic, readonly) NSArray *overlays;


- (void)setCenterCoordinate:(CLLocationCoordinate2D)coordinate animated:(BOOL)animated;
- (void)setRegion:(MKCoordinateRegion)region animated:(BOOL)animated;

// Overlays
- (void)addOverlay:(id < MKOverlay >)overlay;
- (void)addOverlays:(NSArray *)overlays;
- (void)exchangeOverlayAtIndex:(NSUInteger)index1 withOverlayAtIndex:(NSUInteger)index2;
- (void)insertOverlay:(id < MKOverlay >)overlay aboveOverlay:(id < MKOverlay >)sibling;
- (void)insertOverlay:(id < MKOverlay >)overlay atIndex:(NSUInteger)index;
- (void)insertOverlay:(id < MKOverlay >)overlay belowOverlay:(id < MKOverlay >)sibling;
- (void)removeOverlay:(id < MKOverlay >)overlay;
- (void)removeOverlays:(NSArray *)overlays;
- (MKOverlayView *)viewForOverlay:(id < MKOverlay >)overlay;

@end


@protocol MKMapViewDelegate <NSObject>
@optional

- (void)mapView:(MKMapView *)mapView regionWillChangeAnimated:(BOOL)animated;
- (void)mapView:(MKMapView *)mapView regionDidChangeAnimated:(BOOL)animated;

- (void)mapViewWillStartLoadingMap:(MKMapView *)mapView;
- (void)mapViewDidFinishLoadingMap:(MKMapView *)mapView;
- (void)mapViewDidFailLoadingMap:(MKMapView *)mapView withError:(NSError *)error;

// mapView:viewForAnnotation: provides the view for each annotation.
// This method may be called for all or some of the added annotations.
// For MapKit provided annotations (eg. MKUserLocation) return nil to use the MapKit provided annotation view.
//- (MKAnnotationView *)mapView:(MKMapView *)mapView viewForAnnotation:(id <MKAnnotation>)annotation;

// mapView:didAddAnnotationViews: is called after the annotation views have been added and positioned in the map.
// The delegate can implement this method to animate the adding of the annotations views.
// Use the current positions of the annotation views as the destinations of the animation.
//- (void)mapView:(MKMapView *)mapView didAddAnnotationViews:(NSArray *)views;

// mapView:annotationView:calloutAccessoryControlTapped: is called when the user taps on left & right callout accessory UIControls.
//- (void)mapView:(MKMapView *)mapView annotationView:(MKAnnotationView *)view calloutAccessoryControlTapped:(UIControl *)control;

// Overlays
- (MKOverlayView *)mapView:(MKMapView *)mapView viewForOverlay:(id <MKOverlay>)overlay;
- (void)mapView:(MKMapView *)mapView didAddOverlayViews:(NSArray *)overlayViews;


// iOS 4.0 additions:
- (void)mapView:(MKMapView *)mapView didUpdateUserLocation:(MKUserLocation *)userLocation;
- (void)mapView:(MKMapView *)mapView didFailToLocateUserWithError:(NSError *)error;
- (void)mapViewWillStartLocatingUser:(MKMapView *)mapView;
- (void)mapViewDidStopLocatingUser:(MKMapView *)mapView;



@end
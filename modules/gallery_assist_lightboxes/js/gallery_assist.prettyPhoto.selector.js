// $Id: gallery_assist.prettyPhoto.selector.js,v 1.3 2009/10/18 19:15:52 jcmc Exp $
// drupal_add_js(drupal_get_path('module', 'gallery_assist_lightboxes')  .'/js/gallery_assist.prettyPhoto.selector.js');

$(document).ready(function(){
  var mytheme = Drupal.settings.lightbox_conf['prettyPhoto']['theme'];
  var mycounter_separator_label = Drupal.settings.lightbox_conf['prettyPhoto']['counter_separator_label'];
  var myanimationSpeed = Drupal.settings.lightbox_conf['prettyPhoto']['animationSpeed'];
  var myopacity = Drupal.settings.lightbox_conf['prettyPhoto']['opacity'];
  var mypadding = Drupal.settings.lightbox_conf['prettyPhoto']['padding'];
  var myshowTitle = Drupal.settings.lightbox_conf['prettyPhoto']['showTitle'];
  var myallowresize = Drupal.settings.lightbox_conf['prettyPhoto']['allowresize'];

  if (mytheme.length == 0) {
    mytheme = 'dark_square';
  }
  if (mycounter_separator_label.length == 0) {
    mycounter_separator_label = '/';
  }
  if (myanimationSpeed.length == 0) {
    myanimationSpeed = 'normal';
  }
  if (myopacity.length == 0) {
    myopacity = 0.9;
  }      
  if (mypadding.length == 0) {
    mypadding = '40';
  }      
  if (myshowTitle.length == 0) {
    myshowTitle = false;
  } else {
    myshowTitle = parseInt(myshowTitle);
  }
  if (myallowresize.length == 0) {
    myallowresize = true;
  } else {
    myallowresize = parseInt(myallowresize);
  }

  $("a[rel^='prettyPhoto']").prettyPhoto({
    //animationSpeed: 'normal', /* fast/slow/normal */
    animationSpeed: myanimationSpeed,
    //padding: 40, /* padding for each side of the picture */
    padding: parseInt(mypadding), /* padding for each side of the picture */
    //opacity: 0.9, /* Value betwee 0 and 1 */
    opacity: myopacity,
    //showTitle: false, /* true/false */
    showTitle: myshowTitle,
    //allowresize: true, /* true/false */
    allowresize: myallowresize,
    //counter_separator_label: '/', /* The separator for the gallery counter 1 "of" 2 */
    counter_separator_label: mycounter_separator_label,
    //theme: 'dark_rounded', /* light_rounded / dark_rounded / light_square / dark_square */
    theme: mytheme,
    callback: function(){}
  });
});

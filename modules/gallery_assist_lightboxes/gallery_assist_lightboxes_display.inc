<?php
// $Id: gallery_assist_lightboxes_display.inc,v 1.4 2009/11/11 13:33:32 jcmc Exp $

/**
 * @file
 * Display the gallery container, the items are linkend with lightbox functionality.
 */

/**
 * Display gallery container. 
 */
function gallery_assist_display($node, $opt='', $owner='') {
  global $user;

  $conf = $node->gallconf[$node->type];
  $conf['lightbox'] = variable_get('gallery_assist_lightbox', 'none') == 'none' ? 0 : 1;
  $conf['lightbox_deriv'] = $conf['lightbox'] == 1 ? variable_get('gallery_assist_lightbox', 'none') : '';

  $my_teaser_count = $conf['items_per_row'];
  $my_page_count = $conf['items_per_row'] == 'unlimited' ? count($node->gallitems) : $conf['items_per_row'] * $conf['rows_per_page'];
  if ($conf['items_per_row'] == 'unlimited' && $opt == 'teaser') {
    $my_teaser_count = 3;
  }
  $my_previous = '‹ previous';
  $my_next = 'next ›';
  
  if (count($node->gallitems) == 0) { 
    return; 
  }

  foreach ($node->gallitems as $pid => $item) {
    $img_obj = image_get_info($item->tpath);

    if ($img_obj['width'] > $img_obj['height']) { 
      $img_obj['layout'] = 'h'; 
    }
    else { 
      $img_obj['layout'] = 'v'; 
    }

    foreach ($img_obj as $k => $v) {
      $node->gallitems[$pid]->$k = $v;
      $node->gallitems[$pid]->show_title = $node->show_title;
    }

    $my_item_box = gallery_assist_item_box($node->type, $node->gallitems[$pid], $conf, $img_obj);
    $my_boxes[] = $my_item_box;
  }

  // Prepare the pager OLD VARIANT OF gallery_assist.
  $node->gall_pager->show = $my_page_count;

  $node->gall_pager->cshow = $node->gall_pager->show;

  $theme = $user->theme ? $user->theme : variable_get('theme_default', FALSE);
  $my_pager_layout = $conf['pager_layout'];

  $my_grafic_next_path = file_exists(drupal_get_path('theme', $theme) .'/ga_pager/'. $my_pager_layout .'/next.png') ? drupal_get_path('theme', $theme) .'/ga_pager/'. $my_pager_layout .'/next.png' : drupal_get_path('module', 'gallery_assist') .'/ga_pager/default/next.png';
  $my_grafic_next = theme('image', $my_grafic_next_path, '', 'go to the next');
  $my_next = $conf['pager_symbol'] == 0 ? t('next ›') : $my_grafic_next;
  $my_grafic_previous_path = file_exists(drupal_get_path('theme', $theme) .'/ga_pager/'. $my_pager_layout .'/previous.png') ? drupal_get_path('theme', $theme) .'/ga_pager/'. $my_pager_layout .'/previous.png' : drupal_get_path('module', 'gallery_assist') .'/ga_pager/default/previous.png';
  $my_grafic_previous = theme('image', $my_grafic_previous_path, '', 'go to the previous');
  $my_previous = $conf['pager_symbol'] == 0 ? t('‹ previous') : $my_grafic_previous;

  $my_separator = $conf['pager_symbol'] == 0 ? ' | ' : '&nbsp;&nbsp;&nbsp;';

  if ($_GET['page'] == '' || $_GET['page'] == 1) {
    $pages = 0;
    $page = 2;
    $preview = '';
    if (count($my_boxes) <= $node->gall_pager->show) {
      $next = "";
    }
    else {
      $next = l($my_next, $_GET['q'], array('html' => TRUE, 'attributes' => array('class' => $node->type .' pager-next'), 'query' => array('page' => $page, 'titles' => $_GET['titles'])));
    }
  }
  else {
    $pages = $node->gall_pager->show * ($_GET['page'] - 1);
    $page = $_GET['page'];
    $node->gall_pager->cshow = $node->gall_pager->show * $_GET['page'];
    
    $preview = l($my_previous, $_GET['q'], array('html' => TRUE, 'attributes' => array('class' => $node->type .' pager-previous'), 'query' => array('page' => ($_GET['page'] - 1), 'titles' => $_GET['titles'])));
    if ($node->gall_pager->cshow < count($my_boxes)) {
      $next = l($my_next, $_GET['q'], array('html' => TRUE, 'query' => array('page' => ($_GET['page'] + 1), 'titles' => $_GET['titles'])));
    }
    else {
      $next = "";
    }
  }

  if (!empty($preview)) $link[] = $preview;
  if (!empty($next)) $link[] = $next;

  switch ($opt) {
    case 'teaser':
    for ($i = 0; $i < $my_teaser_count; $i++) {
      $boxes .= $my_boxes[$i];
      unset($my_boxes[$i]);
    }
    $node->gallconf[$node->type]['op'] = 'teaser';
    break;

    case 'page': 
    for ($i=$pages; $i < $node->gall_pager->cshow; $i++) {
      if (drupal_strlen($my_boxes[$i]) > 0) {
        $count[] =  1;
      }
      $boxes .= $my_boxes[$i];
      unset($my_boxes[$i]);
    }
    $node->gallconf[$node->type]['op'] = 'page';
    break;

  }

  $invlisten = '<div style="display:none;">'. implode("\n", $my_boxes) .'</div>';

  $extras['container_width'] = $conf['container_width'];
  $extras['pager_position'] = $conf['pager_position'];
  if (count($node->gallitems) > $node->gall_pager->show && $opt == 'page') {
    $links = implode($my_separator, $link);
    
    $pager .= theme('gallery_assist_pager', $links, $extras);
  }

  $hilfo = variable_get('gallery_assist_lightboxes_files', FALSE);
  if ($conf['lightbox'] == 1 && $conf['lightbox_deriv'] == 'prettyPhoto') {
    drupal_add_css(drupal_get_path('module', 'gallery_assist_lightboxes') .'/lightboxes/prettyPhoto/css/prettyPhoto.css');
    drupal_add_js(drupal_get_path('module', 'gallery_assist_lightboxes')  .'/lightboxes/prettyPhoto/js/jquery.prettyPhoto.js');
    drupal_add_js(drupal_get_path('module', 'gallery_assist_lightboxes')  .'/js/gallery_assist.prettyPhoto.selector.js', 'module', 'header');
    //gallery_assist_get_includes($hilfo);
    drupal_add_js(drupal_get_path('module', 'gallery_assist_lightboxes')  .'/js/gallery_assist.prettyPhoto.selector.js', 'module', 'header');
  }
  elseif ($conf['lightbox'] == 1 && $conf['lightbox_deriv'] == 'lytebox' || $conf['lightbox_deriv'] == 'lyteshow') {
    drupal_add_css(drupal_get_path('module', 'gallery_assist_lightboxes') .'/lightboxes/lytebox/lytebox.css');
    drupal_add_js(drupal_get_path('module', 'gallery_assist_lightboxes')  .'/lightboxes/lytebox/lytebox.js');
  }
  elseif ($conf['lightbox'] == 1 && $conf['lightbox_deriv'] == 'thickbox') {
    drupal_add_css(drupal_get_path('module', 'gallery_assist_lightboxes') .'/lightboxes/thickbox/css/thickbox.css');
    drupal_add_js(drupal_get_path('module', 'gallery_assist_lightboxes')  .'/lightboxes/thickbox/js/thickbox.js');
  }
  elseif ($conf['lightbox'] == 1 && $conf['lightbox_deriv'] == 'lightbox') {
    //drupal_add_css(drupal_get_path('module', 'gallery_assist_lightboxes') .'/lightboxes/lightbox/css/lightbox.css');
    //drupal_add_js(drupal_get_path('module', 'gallery_assist_lightboxes')  .'/lightboxes/lightbox/js/prototype.js');
    //drupal_add_js(drupal_get_path('module', 'gallery_assist_lightboxes')  .'/lightboxes/lightbox/js/scriptaculous.js');
    //drupal_add_js(drupal_get_path('module', 'gallery_assist_lightboxes')  .'/lightboxes/lightbox/js/lightbox.js');
    gallery_assist_get_includes($hilfo);
  }
  elseif ($conf['lightbox'] == 1 && $conf['lightbox_deriv'] == 'fancybox') {
    //drupal_add_css(drupal_get_path('module', 'gallery_assist_lightboxes') .'/lightboxes/fancybox/jquery.fancybox.css');
    //drupal_add_js(drupal_get_path('module', 'gallery_assist_lightboxes')  .'/lightboxes/fancybox/jquery.easing.1.3.js');
    //drupal_add_js(drupal_get_path('module', 'gallery_assist_lightboxes')  .'/lightboxes/fancybox/jquery.fancybox-1.2.2.pack.js');
    gallery_assist_get_includes($hilfo);
    drupal_add_js(drupal_get_path('module', 'gallery_assist_lightboxes')  .'/js/gallery_assist.fancybox.selector.js');
  }
  elseif ($conf['lightbox'] == 1 && $conf['lightbox_deriv'] == 'colorbox') {
    //drupal_add_css(drupal_get_path('module', 'gallery_assist_lightboxes') .'/lightboxes/fancybox/jquery.fancybox.css');
    //drupal_add_js(drupal_get_path('module', 'gallery_assist_lightboxes')  .'/lightboxes/fancybox/jquery.easing.1.3.js');
    //drupal_add_js(drupal_get_path('module', 'gallery_assist_lightboxes')  .'/lightboxes/fancybox/jquery.fancybox-1.2.2.pack.js');
    gallery_assist_get_includes($hilfo);
    drupal_add_js(drupal_get_path('module', 'gallery_assist_lightboxes')  .'/js/gallery_assist.colorbox.selector.js');
  }
  elseif ($conf['lightbox'] == 1 && $conf['lightbox_deriv'] == 'shadowbox') {
    //drupal_add_css(drupal_get_path('module', 'gallery_assist_lightboxes') .'/lightboxes/'. $conf['lightbox_deriv'] .'/shadowbox.css');
    //drupal_add_js(drupal_get_path('module', 'gallery_assist_lightboxes')  .'/lightboxes/'. $conf['lightbox_deriv'] .'/shadowbox.js');
    gallery_assist_get_includes($hilfo);
    drupal_add_js(drupal_get_path('module', 'gallery_assist_lightboxes')  .'/js/gallery_assist.shadowbox.selector.js');
  }
  elseif ($conf['lightbox'] == 1 && $conf['lightbox_deriv'] == 'MultiBox') {
    gallery_assist_get_includes($hilfo);
    //drupal_add_js(drupal_get_path('module', 'gallery_assist_lightboxes')  .'/js/gallery_assist.shadowbox.selector.js');
  }
  elseif ($conf['lightbox'] == 1 && $conf['lightbox_deriv'] == 'milkbox') {
    gallery_assist_get_includes($hilfo);
  }
  elseif ($conf['lightbox'] == 1 && $conf['lightbox_deriv'] == 'highslide') {
    gallery_assist_get_includes($hilfo);
    //drupal_add_js(drupal_get_path('module', 'gallery_assist_lightboxes')  .'/js/gallery_assist.highslide.selector.js');
  }  
  return theme('gallery_assist_display', $pager, $boxes.$invlisten, $node->gallconf[$node->type], $node->type);
}

function gallery_assist_get_includes($hilfo = array()) {
  if (empty($hilfo)) {
    return;
  }
  
  if (count($hilfo['data']['css'])) {
    foreach ($hilfo['data']['css'] as $k => $v) {
      if ($v) {
        drupal_add_css($k);
      }
    }
  }
  
  if (count($hilfo['data']['js'])) {
    foreach ($hilfo['data']['js'] as $k => $v) {
      if ($v) {
        drupal_add_js($k);
      }
    }
  } 
  
  if (count($hilfo['data']['selector'])) {
    foreach ($hilfo['data']['selector'] as $k => $v) {
      if ($v) {
        drupal_add_js($k);
      }
    }
  }
}

/**
 * Build and return the gallery item box.
 */
function gallery_assist_item_box($type, &$item, $conf, $img) {
  global $user;

  $format_display = $conf['format_display'] == 'grid' ? 'float:left;' : '';

  $item->nodetype = $type;
  $my_title_height = $item->show_title == 1 && $conf['thumbnail_size'] >= 100 ? 30 : 0;
  $my_item_width = $conf['thumbnail_size'] + $conf['thumbnail_width_plus'] + ($conf['item_padding'] * 2) + ($conf['item_border'] * 2);
  $my_item_height = $conf['thumbnail_size'] + ($conf['item_padding'] * 2) + ($conf['item_border'] * 2) + $my_title_height;

  $my_item_attr = array(
    'id' => 'item-box-'. $item->pid,
    'class' => $type .' item-box',
    'style' => 'height:'. $my_item_height .'px;width:'. $my_item_width .'px;'. $format_display,
  );

  if ($conf['item_margin'] > 0) {
    $my_item_attr['style'] .= 'margin:'. $conf['item_margin'] .'px;';
  }

  $link = l('edit', 'node/gallery_assist/'. $item->nid .'/'. $item->pid); // , array('query' => '#'. $item->pid)
  $a_link = '<div id="image-box-'. $item->pid .'-links" class="'. $type .' image-box-links">[ '. $link .' ]</div>'."\n";

  $ga_item_attr = drupal_attributes($my_item_attr);
  $ga_edit_link = $user->uid == $item->uid ? $a_link : '';
  $ga_item_box = gallery_assist_image_box($type, $item, $conf, $img);
  $ga_item_title = $item->show_title == 1 && $conf['thumbnail_size'] >= 100 ? gallery_assist_title_box($item, $conf) : '';

  $output = theme('gallery_assist_item_box', $ga_item_box, $ga_item_title, $ga_edit_link, $ga_item_attr);

  return $output;
}

function theme_gallery_assist_item_box($ga_item_box, $ga_item_title, $ga_edit_link, $ga_item_attr) {
  $output  = '<div'. $ga_item_attr .'>'."\n";
  $output .= $_GET['links'] == 'on' ? $ga_edit_link : '';
  $output .= $ga_item_box;
  $output .= $ga_item_title;
  $output .= '</div>'."\n";

  return $output;
}

/**
 * Build and return the image box. 
 */
function gallery_assist_image_box($type, &$item, $conf, $img) {
  global $base_url;
  $conf['shadow'] = 1;

  if ($conf['shadow'] == 1) {
    $withshadow = ' shadow3';
    drupal_add_css(drupal_get_path('module', 'gallery_assist') .'/css/gallery_assist_shadow.css', 'module', 'all', FALSE);
  }

  $my_box_attr = array(
    'id' => 'image-box-'. $item->pid,
    'class' => $type .' image-box'. $withshadow,
    'style' => 'height:'. $conf['thumbnail_size'] + ($conf['item_padding'] * 2) .'px;'.
               'width:'. $conf['thumbnail_size'] + ($conf['item_padding'] * 2) .'px;',
  );

  if ($conf['item_padding'] > 0) {
    $my_box_attr['style'] .= 'padding:'. $conf['item_padding'] .'px;';
  }

  if ($conf['item_border'] > 0) {
    $my_box_attr['style'] .= 'border:'. $conf['item_border'] .'px solid '. $conf['item_border_color'] .';';
  }
  
  $sheet_plus = $conf['thumbnail_size'] + $conf['thumbnail_height_plus'];
  $my_sheet_attr = array(
    'id' => 'image-sheet-'. $item->pid,
    'class' => $type .' image-sheet'. $my_img_behavior,
    'style' => 'height:'. $sheet_plus .'px;'.
               'width:'. $conf['thumbnail_size'] .'px;',
  );

  $img = gallery_assist_image_more_info($type, $img, $conf);

  $my_layout = $img['pos'] == 'v' ? 'height' : 'width';
  $my_img_attr = array(
    $my_layout => $conf['thumbnail_size'] .'px',
    'style' => 'margin-top:'. $img['top'] .'px;',
  );

  if ($conf['use_imagecache'] == 1) {
    $my_img = theme('imagecache', $conf['thm_presetname'], $item->opath, $item->palt, $item->ptitle, $my_img_attr, FALSE);
  }
  else {
    $my_img = theme('image', $item->tpath, $item->palt, $item->ptitle, $my_img_attr, FALSE);
  }

  if ($conf['lightbox'] == 1 && $conf['lightbox_deriv'] == 'prettyPhoto') {
    $my_item_link = l($my_img, $base_url .'/'. $item->ppath, array('attributes' => array('class' => 'prettyPhoto', 'rel' => 'prettyPhoto[gallery'. $item->gid .']'),'html' => TRUE));
  }
  elseif ($conf['lightbox'] == 1 && $conf['lightbox_deriv'] == 'lytebox') {
    $my_item_link = l($my_img, $base_url .'/'. $item->ppath, array('attributes' => array('caption' => $item->description, 'title' => $item->ptitle, 'rel' => 'lytebox['. $item->nid.']'), 'html' => TRUE));
  }
  elseif ($conf['lightbox'] == 1 && $conf['lightbox_deriv'] == 'lyteshow') {
    $my_item_link = l($my_img, $base_url .'/'. $item->ppath, array('attributes' => array('caption' => $item->description, 'title' => $item->ptitle, 'rel' => 'lyteshow['. $item->nid.']'), 'html' => TRUE));
  }
  elseif ($conf['lightbox'] == 1 && $conf['lightbox_deriv'] == 'thickbox') {
    $my_item_link = l($my_img, $base_url .'/'. $item->ppath, array('attributes' => array('class' => 'thickbox', 'rel' => $item->nid), 'html' => TRUE));
  }
  elseif ($conf['lightbox'] == 1 && $conf['lightbox_deriv'] == 'lightbox') {
    $my_item_link = l($my_img, $base_url .'/'. $item->ppath, array('attributes' => array('rel' => 'lightbox['. $item->nid.']'), 'html' => TRUE));
  }
  elseif ($conf['lightbox'] == 1 && $conf['lightbox_deriv'] == 'fancybox') {
    $my_item_link = l($my_img, $base_url .'/'. $item->ppath, array('attributes' => array('title' => $item->ptitle, 'rel' => $item->nid), 'html' => TRUE));
  }
  elseif ($conf['lightbox'] == 1 && $conf['lightbox_deriv'] == 'colorbox') {
    $my_item_link = l($my_img, $base_url .'/'. $item->ppath, array('attributes' => array('class' => 'cboxelement', 'rel' => $item->nid), 'html' => TRUE));
  }
  elseif ($conf['lightbox'] == 1 && $conf['lightbox_deriv'] == 'shadowbox') {
    $my_item_link = l($my_img, $base_url .'/'. $item->ppath, array('attributes' => array('rel' => 'shadowbox['. $item->nid .']'), 'html' => TRUE));
  }
  elseif ($conf['lightbox'] == 1 && $conf['lightbox_deriv'] == 'milkbox') {
    $my_item_link = l($my_img, $base_url .'/'. $item->ppath, array('attributes' => array('rel' => 'milkbox['. $item->nid .']'), 'html' => TRUE));
  }
  elseif ($conf['lightbox'] == 1 && $conf['lightbox_deriv'] == 'MultiBox') {
    $my_item_link = l($my_img, $base_url .'/'. $item->ppath, array('attributes' => array('class' => 'multiBoxDesc '. $item->nid), 'html' => TRUE));
  }
  elseif ($conf['lightbox'] == 1 && $conf['lightbox_deriv'] == 'highslide') {
    $my_item_link = l($my_img, $base_url .'/'. $item->ppath, array('attributes' => array('title' => $item->ptitle, 'class' => 'highslide ', 'onclick' => 'return hs.expand(this, { slideshowGroup: '. $item->nid .' })'), 'html' => TRUE));
  }
  else {
    $item_link = 'node/'. $item->nid .'/'. $item->pid;
    $my_item_link = l($my_img, $item_link, array('html' => TRUE));
  }

  $output  = '<div'. drupal_attributes($my_box_attr) .'>'."\n";
  $output .= '  <div'. drupal_attributes($my_sheet_attr) .'>'."\n";
  $output .= '    '. $my_item_link;
  $output .= '  </div>'."\n";
  $output .= '</div>'."\n";

  return $output;
}

/**
 * Build and return the gallery item box. 
 */
function gallery_assist_image_more_info($type, $img, $conf) {
  $symbol = $conf['thumbnail_size'];
  $img['padding'] = $conf['item_padding'];
  $img['margin'] = $conf['item_margin'];
  $img['dsize'] = $conf['thumbnail_size'];

  $img['pos'] = $img['height'] >= $img['width'] ? 'v' : 'h';

  if ($img['pos'] == 'h') {
    $img['new_width'] = $symbol;
    $img['new_height'] = ((($img['new_width'] * 100) / $img['width']) * $img['height']) / 100;
    $img['top'] = ($symbol - $img['new_height']) / 2;
  }
  else {
    $img['new_height'] = $symbol;
  }

  return $img;
}

/**
 * Build and return the item title box. 
 */
function gallery_assist_title_box(&$item, $conf) {
  $points = drupal_strlen($item->ptitle) > $conf['title_substr'] ? "..." : '';
  $title = drupal_substr($item->ptitle, 0, $conf['title_substr']) . $points;

  $output  = '<div id="title-box-'. $item->pid .'" class="'. $item->nodetype .' title-box">'."\n";
  $output .= l($title, 'node/'. $item->nid .'/'. $item->pid, array('html' => TRUE, 'attributes' => array('title' => $item->ptitle)));
  $output .= '</div>'."\n";

  return $output;
}

/**
 * Theme the item output.
 */
function theme_gallery_assist_display(&$pager, &$boxes, $conf, $type = 'gallery_assist') {
  $my_attr_array = array(
    'style' => 'width:'. $conf['container_width'] .'px',
  );

  $my_attr = $conf['items_per_row'] == 'unlimited' ? '' : drupal_attributes($my_attr_array);
  $galleriffic = '<div id="controls"></div>
<div id="loading"></div>
<div id="slideshow"></div>
<div id="caption"></div>';
  
  $output  = '<div id="gallery-container" class="'. $type .' gallery-container '. $conf['op'] .' clear-block"'. $my_attr .'>';
  if ($conf['lightbox_deriv'] == 'galleriffic') { $output .= $galleriffic; }
  $output .= $conf['pager_position'] == 'top' || $conf['pager_position'] == 'both' ? $pager : '';
  $output .= $boxes;
  $output .= $conf['pager_position'] == 'bottom' || $conf['pager_position'] == 'both' ? $pager : '';
  $output .= '</div>';

  return  $output;
}


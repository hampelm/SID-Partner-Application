<?php

function drupify_breadcrumb($breadcrumb) {
  if (!empty($breadcrumb)) {
    $bcimage = ' <img src="'. base_path() . path_to_theme() .'/images/arrow.png"> ';  
    return '<div class="breadcrumb">'. implode($bcimage, $breadcrumb) .'</div>';
  }
}

?>

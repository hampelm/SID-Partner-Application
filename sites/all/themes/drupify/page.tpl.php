<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
    "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
  <head>
    <meta name="generator" content="HTML Tidy for Windows (vers 14 February 2006), see www.w3.org" />
    <title>
      <?php print $head_title; ?>
    </title>
    <?php print $head; ?>
    <?php print $styles; ?>
    <?php print $scripts; ?>
<!--[if lte IE 6]>
<link href="<?php print $base_path . $directory; ?>/css/template_ie.css" rel="stylesheet" type="text/css" />
<![endif]-->
  </head>
  <body id="page_bg">
    <div id="wrapper">
      <div id="header">
        <div class="rk-1">
          <div class="rk-2">
            <?php if ($logo): ?>
              <a href="<?php print $base_path; ?>" title="<?php print t('Home'); ?>">
              <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" id="logo" />
              </a>
            <?php endif; ?>
            <div id="top">
              <div class="padding">
                <table class="contentpaneopen">
                  <tr>
                    <td valign="top" colspan="2">
                      <?php if ($header): ?>
                        <div id="header_block" class="header">
                          <?php print $header; ?>
                        </div> <!-- /header -->
                      <?php endif; ?>                      
                    </td>
                  </tr>
                </table>
              </div>
            </div>
          </div>
        </div>
      </div>
      <div id="horiz-menu">
        <div id="navigation" class="menu">
				  <?php if (isset($primary_links)) : ?>      
            <div id="primary" class="clear-block">
              <?php print theme('links', $primary_links, array('class' => 'links primary-links')) ?>
            </div>
          <?php endif; ?>
            
        </div> <!-- /navigation -->      
      </div>
      <div id="mainbody">
        <table class="mainbody" cellspacing="0" cellpadding="0">
          <tr valign="top">
            <td class="mainbody">
              <?php if ($top_left or $top_right): ?>
                <table class="usermodules" cellspacing="15">
                  <tr valign="top">
                    <td class="usermodules">
                      <div class="moduletable">
                        <?php if ($top_left): ?>
                          <div id="top_left" class="column sidebar">
                            <?php print $top_left; ?>
                          </div> <!-- /top_left -->
                        <?php endif; ?>
                      </div>
                    </td>
                    <td class="usermodules">
                      <div class="moduletable">
                        <?php if ($top_right): ?>
                          <div id="top_right" class="column sidebar">
                            <?php print $top_right; ?>
                          </div> <!-- /top_right -->
                        <?php endif; ?>
                      </div>
                    </td>
                  </tr>
                </table>
              <?php endif; ?>
              <div class="padding">
                <?php if ($breadcrumb): ?>
                  <div id="header-region">
                    <?php print $breadcrumb; ?>
                  </div>
                <?php endif; ?>
                <table class="blog" cellpadding="0" cellspacing="0">
                  <tr>
                    <td valign="top">
                      <div>
                        <table class="contentpaneopen">
                        </table>
                        <table class="contentpaneopen">
                          <tr>
                            <td valign="top" colspan="2">
                              <div id="main" class="column"><div id="squeeze">
                                <?php if ($content_top):?><div id="content-top"><?php print $content_top; ?></div><?php endif; ?>
                                <?php if ($title): ?><h1 class="title"><?php print $title; ?></h1><?php endif; ?>
                                <?php if ($tabs): ?><div class="tabs"><?php print $tabs; ?></div><?php endif; ?>
                                <?php print $help; ?>
                                <?php print $messages; ?>
                                <?php print $content; ?>
                                <?php print $feed_icons; ?>
                                <?php if ($content_bottom): ?><div id="content-bottom"><?php print $content_bottom; ?></div><?php endif; ?>
                              </div></div> <!-- /squeeze /main -->
                            </td>
                          </tr>
                        </table>
                      </div>
                    </td>
                  </tr>
                </table>
              </div>
            </td>
            <td class="right">
              <div class="padding">
                <div class="moduletable">
                  <?php if ($left || $right): ?>
                    <div id="sidebar-right" class="column sidebar">
                      <?php if ($secondary_links): ?>
                        <div id="secondary" class="clear-block">
                          <?php print theme('links', $secondary_links, array('class' => 'links secondary-links')) ?>
                        </div>
                      <?php endif; ?>
                    
                      <?php if ($left) {  print $left; } ?>
                      <?php if ($right) { print $right; } ?>
                    </div> <!-- /sidebar-right -->
                  <?php endif; ?>
                </div>
              </div>
            </td>
          </tr>
        </table>
      </div>
      <div id="bottom">
        <table class="usermodules" cellspacing="15">
          <tr valign="top">
            <td class="usermodules">
              <div class="moduletable">
                <?php if ($bottom_left): ?>
                  <div id="bottom_left" class="column sidebar">
                    <?php print $bottom_left; ?>
                  </div> <!-- /bottom_left -->
                <?php endif; ?>
              </div>
            </td>
            <td class="usermodules">
              <div class="moduletable">
                <?php if ($bottom_right): ?>
                  <div id="bottom_right" class="column sidebar">
                    <?php print $bottom_right; ?>
                  </div> <!-- /bottom_right -->
                <?php endif; ?>
              </div>
            </td>
          </tr>
        </table>
      </div>
      <div id="footer">
        <div class="rk-1">
          <div class="rk-2">
            <div id="the-footer">
              <a href="http://www.rockettheme.com/" title="RocketTheme Joomla Template Club" class="nounder"><img src="http://demo.rockettheme.com/rokwebify/images/blank.png" border="0" alt="RocketTheme Joomla Templates" id="rocket" name="rocket" /></a>
            </div>
          </div>
        </div>
      </div>
    </div><!-- 1189991641 -->
  <?php print $closure ?>
  </body>
</html>

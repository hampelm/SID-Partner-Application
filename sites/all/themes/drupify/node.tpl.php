<div class="node <?php print $node_classes ?>" id="node-<?php print $node->nid; ?>"><div class="node-inner">

  <?php if ($page == 0): ?>
    <h1 class="title contentheading">
      <a href="<?php print $node_url; ?>"><?php print $title; ?></a>
    </h1>
  <?php endif; ?>

  <?php if ($picture) print $picture; ?>

  <?php if ($submitted): ?>
    <div class="submitted">
      <?php print $submitted; ?>
    </div>
  <?php endif; ?>

  <?php if (count($taxonomy)): ?>
    <div class="taxonomy"><?php print t(' in ') . $terms; ?></div>
  <?php endif; ?>

<?php
// Check function exists, so theme doesn't break if  favorite_nodes disabled
if ( function_exists('favorite_nodes_link') ) {
  // Same function PHPTemplate uses
  print theme(
    'links',
    // Call the hook_link from the favorite_nodes module directly
    favorite_nodes_link('node', $node),
    array('class' => 'links inline favorite-links')
  );
}
?>

  <div class="content">
    <?php print $content; ?>
  </div>

  <?php if ($links): ?>
    <div class="links">
      <?php print $links; ?>
    </div>
  <?php endif; ?>

</div></div> <!-- /node-inner, /node -->

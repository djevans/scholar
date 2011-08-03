<br/>
<?php
print theme_fieldset(array(
      '#title' => t("Technical Details"),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
      '#children' => theme_table(array(
        array(
          'colspan' => 3,
          'data' => 'Technical Details'
        ),
        array(
          'data' => 'Mime Type'
          )), $rows)
    ));
?>
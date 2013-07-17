<h3>
<?php
echo $_eHinweis[0]; // 1. Hinweis anzeigen
array_splice($_eHinweis, 0, 1); // zum naechsten Hinweis schalten
?>
</h3>
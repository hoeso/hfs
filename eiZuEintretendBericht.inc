<?
$BERICHTNR_HIGH=18; // hier HIGH + 1 setzen !!
if( isset( $_SERVER['BerichteRoot'] ) )
  $BERICHT_ROOT=$_SERVER['BerichteRoot'];
else
  $BERICHT_ROOT="/var/www/berichte/";
$BERICHT_WEBALIAS="/berichte/";
// vergebene Bericht-Nummern
$LETTER_VN=13; // Adresse im Briefbogen: Versicherer ueberschreiben mit VN-Adresse
$LETTER_AST=14; // Adresse im Briefbogen: Versicherer ueberschreiben mit AST-Adresse
$LETTER_PARTNER=15; // Adresse im Briefbogen: Versicherer ueberschreiben mit Partner-Adresse
?>

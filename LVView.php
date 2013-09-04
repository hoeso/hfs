<?php
require_once("LVModel.php");
class LVView extends LVModel
{
  private $lvID;

  function __construct($lvID, $d, $thema=1, $czeile=0, $fRec=0, $mode="r")
  {
    $this->lvID = $lvID;
    parent::__construct($d, $thema, $czeile, $fRec, $mode);
  }
  function __get($var)
  {
    switch($var)
    {
      case 'vollTreffer': // vor dem naechsten erkannten Token kamen erst Zeilen mit nicht erkannten Token
        return parent::__get('vollTreffer');
      case 'lesbar':
        return parent::__get('lesbar');
      case 'gibLaengeReihe':
        return parent::__get('gibLaengeReihe');
      case 'gibPfad':
        return parent::__get('gibPfad');
      case 'gibReihe':
        return parent::__get('gibReihe');
      case 'gibZeile':
        return parent::__get('gibZeile');
      case 'gibZeilenZaehler':
        return parent::__get('gibZeilenZaehler');
      case 'Thema':
        return parent::__get('Thema');
      default:
        throw new Exception("LVView hat keine Eigenschaft $var.", 1 );
      break;
    }
  }
  function thematisieren( &$thema )
  {
    if( false == parent::thematisieren( $thema ) )
    {
      return;
    }
  }
  function display()
  {
    $aS[0]=0;// hier Feld 0 rein = ID
    $aS[1]=1;// hier Feld 1 rein = Titel
    $dimS = count($aS);
    $sl = "SELECT ID, Titel FROM Spalte WHERE " . $this->lvID . "=LVID ORDER BY Nr";
    DB::gibFelderArray( $sl, $aS );
    echo "\n";?><table><?
    /*** Spalten-Beschriftung anzeigen                           ***/
    echo "\n";?><tr><?
    for( $s=0; $s < count($aS); $s += $dimS )
    {
      echo "\n";?><th><?
      echo $aS[$s+1];
      ?></th><?echo "\n";
    }
    ?></tr><?echo "\n";
    $aZ[0]=0;// hier Feld 0 rein = ID
    $aZ[1]=1;// hier Feld 1 rein = Nr
    $dimZ = count($aZ);
    $sl = "SELECT ID, Nr FROM Zeile WHERE " . $this->lvID . "=LVID ORDER BY Nr";
    DB::gibFelderArray( $sl, $aZ );
    /*** Der Reihe nach die Zeilen ausgeben                      ***/
    for( $z=0; $z < count($aZ); $z += $dimZ )
    {
      echo "\n";?><tr><?
      for( $s=0; $s < count($aS); $s += $dimS )
      {
        ?><td><?
        echo Db::gibFeld( "SELECT Inhalt FROM Zelle c JOIN Spalte s ON (c. SpalteID=s.ID) JOIN Zeile z ON (c. ZeileID=z.ID) WHERE " . $aS[$s] . "=s.ID AND " . $aZ[$z] . "=z.ID" );
        ?></td><?
      }
      ?></tr><?echo "\n";
    }
    echo "\n";?></table><?
  }
}

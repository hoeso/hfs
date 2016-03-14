<?php
require_once("KWmodel.php");
include("vektorQuart.prj"); // $quart
class KWview extends KWmodel
{
  protected $tag;

  function __construct($strDate)
  {
    parent::__construct($strDate);
    //var_dump($this->tag); echo "\n<br>";
  }
  function __get($var)
  {
    switch($var)
    {
      case 'Datum':
        return parent::__get('Datum');
      case 'Go':
        return parent::__get('Go');
      case 'Kalenderwoche':
        return parent::__get('Kalenderwoche');
      case 'KWweiter':
        return parent::__get('KWweiter');
      case 'KWzurueck':
        return parent::__get('KWzurueck');
      case 'Stop':
        return parent::__get('Stop');
      default:
        throw new Exception("KWview hat keine Eigenschaft $var.", 1 );
      break;
    }
  }
  function show()
  {
    global $quart;
    ?><table><tr><?php
    /*** 1. Header ausgeben           ***/
    $i=0;
    foreach ($this->tag as $key => $value)
    {
      if( !$i )
      {?>
        <th><a href="">-----</a></th><?php
        ++$i;
	continue;
      }?>
      <th><?php
      echo $key . " " . $value . "    ";
      ?></th><?php
      ++$i;
    }?>
    </tr><tr><?php
    /*** 2. Quart-Zeilen ausgeben     ***/
    $row = $this->Go;
    while( $row < $this->Stop )
    {
      $i=0;
      foreach ($this->tag as $key => $value)
      {
        if( !$i )
        {?>
          <td><?php echo $quart[$row];?></td><?php
          ++$i;
	  continue;
        }?>
        <td><?php
        unset($a);
        $a[0]=0;// hier Feld 0 rein = Menge
        $a[1]=1;// hier Feld 1 rein = Initialen
        $a[2]=2;// hier Feld 2 rein = Name, Vorname
	$dim=3;
        DB::gibFelderArray( "SELECT cv.Menge, CONCAT(LEFT(c.Name,1),LEFT(c.Vorname,1)) AS sc, CONCAT(c.Name,' ',c.Vorname) FROM MAClientVS mcv JOIN ClientVS cv ON (mcv. ClientVSID =cv.ID) JOIN Client c ON (cv. ClientID =c.ID) JOIN Tag t ON (cv. TagID =t.ID) JOIN VS v ON (cv. VSID =v.ID) WHERE '$key'=t.SC AND $row=v.ID ORDER BY sc", $a );
        if( $a[0]==0 && $a[1]==1 && $a[2]==2 )
	{?>
	  <?php
	}
        else
	{
	  for( $k=0; $k < count($a); $k += $dim )
	  {
	    $clutch = $key . $a[$k+1];
	    if ( !isset($aSC) or isset($aSC) and !isset($aSC[$clutch]) )
	    {
	      $aSC[$clutch] = $a[$k];
	    }
	  }
	}
	if( isset($aSC) )
          foreach ($aSC as $sc => &$counter)
	  {
	    if( substr($sc,0,2) == $key )
	    { // sind wir im richtigen Wochentag(=Spalte)?
	      echo substr($sc,2,2) . " "; // nur die Initialen
	      if( $counter )
	        --$counter;
	      if( !$counter )
	        unset($aSC[$sc]);
            }	
	  }
        ?></td><?php
        ++$i;
      }?>
      </tr><tr><?php
      if( !($row % 20) )
      {
        $j=0;
        foreach ($this->tag as $cltch => $datm)
        {
          if( !$j )
          {?>
            <td><a href="">-----</a></td><?php
            ++$j;
        	continue;
          }?>
          <td><?php
          echo $cltch . " " . $datm . "    ";
          ?></td><?php
          ++$j;
        }?>
        </tr><tr><?php
      }
      ++$row;
    }?>
    </tr></table><?php
  }
}

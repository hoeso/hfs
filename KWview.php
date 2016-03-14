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
        echo $key;
        ?></td><?php
        ++$i;
      }?>
      </tr><tr><?php
      ++$row;
    }?>
    </tr></table><?php
  }
}

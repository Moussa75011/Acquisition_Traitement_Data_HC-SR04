

<?php

/*
Programme Php permetant d'afficher les données 
du capteur HC-SR04 
*/
   
exec('mode COM6: BAUD=9600 PARITY=N data=8 stop=1 xon=on');
$fp =fopen("COM6", "w+");

$db = new PDO('sqlite:Us.sqlite');

$db->exec("CREATE TABLE dataUs(
	id INTEGER PRIMARY KEY,
	distance INTEGER,
	heure TIME)"
);


$arrayD = array();
$arrayT = array();


if(!$fp) {
       echo "Error";die();
}

for($i=0; $i<=10; $i++){
    sleep(1);   
    $resulta = fread($fp,10);
    $today = date("H:i:s");

    $dist = ord($resulta);
    $db->exec("INSERT INTO dataUs(distance, heure) VALUES ('$dist','$today')");

    $arrayD[] = $dist;
    $arrayT[] = $today;

   echo ($today);
   echo ("  ");
   echo ord($resulta);
   
    echo "<br>";
    
}

fclose($fp);


/*
require_once ('jpgraph/src/jpgraph.php');
require_once ('jpgraph/src/jpgraph_line.php');
require_once ('jpgraph/src/jpgraph_windrose.php');
$datay1 = array(20,15,23,15);
$datay2 = array(12,9,42,8);
$datay3 = array(5,17,32,24);
//$datay1 = $arrayD;
// Setup the graph
$graph = new Graph(300,250);
$graph->SetScale("textlin");

$theme_class=new UniversalTheme;

$graph->SetTheme($theme_class);
$graph->img->SetAntiAliasing(false);
$graph->title->Set('Données Ultra Son');
$graph->SetBox(false);	

$graph->SetMargin(40,20,36,63);

$graph->img->SetAntiAliasing();

$graph->yaxis->HideZeroLabel();
$graph->yaxis->HideLine(false);
$graph->yaxis->HideTicks(false,false);

$graph->xgrid->Show();
$graph->xgrid->SetLineStyle("solid");
$graph->xaxis->SetTickLabels($arrayT);
$graph->xaxis->SetTextLabelInterval(2);
$graph->xgrid->SetColor('#E3E3E3');
/*
// Create the first line
$p1 = new LinePlot($arrayD);
$p1->value->SetFormat('%d');
$p1->SetColor("#6495ED");
$graph -> Add($p1);
$p1->SetLegend('Line 1');


// Create the first line
$p1 = new LinePlot($datay1);
$graph->Add($p1);
$p1->SetColor("#6495ED");
$p1->SetLegend('Line 1');

// Create the second line
$p2 = new LinePlot($datay2);
$graph->Add($p2);
$p2->SetColor("#B22222");
$p2->SetLegend('Line 2');

// Create the third line
$p3 = new LinePlot($datay3);
$graph->Add($p3);
$p3->SetColor("#FF1493");
$p3->SetLegend('Line 3');

$graph->legend->SetFrameWeight(1);

// Output line
$graph->Stroke("image.png");
//echo ('<img src="image.png">');
*/
?>

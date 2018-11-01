// Copyright © 2002-2010 Microchip Technology Inc.  All rights reserved.
// See Microchip TCP/IP Stack documentation for license information.
// 

// Determines when a request is considered "timed out"
var timeOutMS = 60000; //ms

// Stores a queue of AJAX events to process
var ajaxList = new Array();

// Initiates a new AJAX command
//	url: the url to access
//	container: the document ID to fill, or a function to call with response XML (optional)
//	repeat: true to repeat this call indefinitely (optional)
//	data: an URL encoded string to be submitted as POST data (optional)
function newAJAXCommand(url, container, repeat, data, synchro)
{
    // Set up our object
    var newAjax = new Object();
    var theTimer = new Date();
    newAjax.url = url;
    newAjax.container = container;
    newAjax.repeat = repeat;
    newAjax.ajaxReq = null;

    if (synchro == undefined)
    {
        synchro = true;
    }

    // Create and send the request
    if (window.XMLHttpRequest)
    {
        newAjax.ajaxReq = new XMLHttpRequest();
        newAjax.ajaxReq.open((data == null) ? "GET" : "POST", newAjax.url, synchro);
        newAjax.ajaxReq.send(data);
        // If we're using IE6 style (maybe 5.5 compatible too)
    }
    else
    {
        if (window.ActiveXObject)
        {
            newAjax.ajaxReq = new ActiveXObject("Microsoft.XMLHTTP");
            if (newAjax.ajaxReq)
            {
                newAjax.ajaxReq.open((data == null) ? "GET" : "POST", newAjax.url, synchro);
                newAjax.ajaxReq.send(data);
            }
        }
    }
    newAjax.lastCalled = theTimer.getTime();

    // Store in our array
    ajaxList.push(newAjax);
}

// Loops over all pending AJAX events to determine if any action is required
function pollAJAX()
{
    var curAjax = new Object();
    var theTimer = new Date();
    var elapsed;

    // Read off the ajaxList objects one by one
    for (i = ajaxList.length; i > 0; i--)
    {
        curAjax = ajaxList.shift();
        if (!curAjax)
            continue;
        elapsed = theTimer.getTime() - curAjax.lastCalled;

        // If we suceeded
        if (curAjax.ajaxReq.readyState == 4 && curAjax.ajaxReq.status == 200)
        {
            // If it has a container, write the result
            if (typeof (curAjax.container) == 'function') {
                curAjax.container(curAjax.ajaxReq.responseXML.documentElement);
            } else if (typeof (curAjax.container) == 'string') {
                document.getElementById(curAjax.container).innerHTML = curAjax.ajaxReq.responseText;
            } // (otherwise do nothing for null values)

            curAjax.ajaxReq.abort();
            curAjax.ajaxReq = null;

            // If it's a repeatable request, then do so
            if (curAjax.repeat)
                newAJAXCommand(curAjax.url, curAjax.container, curAjax.repeat);
            continue;
        }

        // If we've waited over 1 second, then we timed out
        if (elapsed > timeOutMS) {
            // Invoke the user function with null input
            if (typeof (curAjax.container) == 'function') {
                curAjax.container(null);
            } /*else {
             // Alert the user
             alert("Connection incorrecte.");
             }*/

            curAjax.ajaxReq.abort();
            curAjax.ajaxReq = null;

            // If it's a repeatable request, then do so
            if (curAjax.repeat)
                newAJAXCommand(curAjax.url, curAjax.container, curAjax.repeat);
            continue;
        }

        // Otherwise, just keep waiting
        ajaxList.push(curAjax);
    }

    // Call ourselves again in 10ms
    setTimeout("pollAJAX()", 10);
}

// Parses the xmlResponse returned by an XMLHTTPRequest object
//	xmlData: the xmlData returned
//  field: the field to search for
function getXMLValue(xmlData, field)
{
    try
    {
        if (xmlData.getElementsByTagName(field)[0].firstChild.nodeValue)
        {
            return xmlData.getElementsByTagName(field)[0].firstChild.nodeValue;
        }
        return null;
    }
    catch (err)
    {
        return null;
    }
}

//kick off the AJAX Updater
setTimeout("pollAJAX()", 100);

//------------------------------------------------------------------------------

function updateHistorique(xmlData)
{
    if (!xmlData)
    {
        return;
    }

    var strIndex = getXMLValue(xmlData, 'ind');
    document.getElementById('op' + strIndex).innerHTML = getXMLValue(xmlData, 'op');
    document.getElementById('date' + strIndex).innerHTML = getXMLValue(xmlData, 'date');
    document.getElementById('heure' + strIndex).innerHTML = getXMLValue(xmlData, 'heure');
    document.getElementById('mch' + strIndex).innerHTML = getXMLValue(xmlData, 'mach');
    document.getElementById('sum' + strIndex).innerHTML = getXMLValue(xmlData, 'sum');
    switch (getXMLValue(xmlData, 'key'))
    {
        case '42':
            document.getElementById('K' + strIndex).innerHTML = 'Indisponible';
            break;
        case '63':
            document.getElementById('K' + strIndex).innerHTML = 'Hors plage horaire';
            break;
        case '65':
            document.getElementById('K' + strIndex).innerHTML = 'Occupee';
            break;
        case "100":
            document.getElementById('K' + strIndex).innerHTML = 'Inactivee';
            break;
        case "101":
            document.getElementById('K' + strIndex).innerHTML = 'Relay off';
            break;
        case "151":
            document.getElementById('K' + strIndex).innerHTML = 'Non existante';
            break;
        case '152':
            document.getElementById('K' + strIndex).innerHTML = 'Vide';
            break;
        case '163':
            document.getElementById('K' + strIndex).innerHTML = 'Secteur abs.';
            break;
        default:
            document.getElementById('K' + strIndex).innerHTML = getXMLValue(xmlData, 'key');
            break;
    }
    cell = document.getElementById('state' + strIndex);
    cell.innerHTML = getXMLValue(xmlData, 'status');
    if (cell.innerHTML === "OK")
    {
        cell.style.backgroundColor = "#0c0";
//        cell.style.backgroundColor = "green"; //Trop sombre
    }
    else
    {
        cell.style.backgroundColor = "red";
    }
}

function updateParameters(xmlData)
{
    // Check if a timeout occurred
    if (!xmlData)
    {
        return;
    }
    document.getElementById("BasePrice").setAttribute("value", getXMLValue(xmlData, "BasePrice"));
    document.getElementById("KeyPrice").setAttribute("value", getXMLValue(xmlData, "KeyPrice"));
    document.getElementById("HHPrice").setAttribute("value", getXMLValue(xmlData, "BasePriceHH"));
    document.getElementById("HHKeyPrice").setAttribute("value", getXMLValue(xmlData, "KeyPriceHH"));
    document.getElementById("Pulse").setAttribute("value", getXMLValue(xmlData, "Pulse"));
    document.getElementById("EnableTimeDisplay").checked = getXMLValue(xmlData, "boRemaining");
    document.getElementById("Displaytime").setAttribute("value", getXMLValue(xmlData, "Displayed"));
    document.getElementById("OverBusy").setAttribute("value", getXMLValue(xmlData, "OverBusy"));
    document.getElementById("StartTime").setAttribute("value", getXMLValue(xmlData, "Start"));
    document.getElementById("EndTime").setAttribute("value", getXMLValue(xmlData, "End"));
    document.getElementById("HHStartTime").setAttribute("value", getXMLValue(xmlData, "StartHH"));
    document.getElementById("HHEndTime").setAttribute("value", getXMLValue(xmlData, "EndHH"));
    document.getElementById("EnableCumul").checked = getXMLValue(xmlData, "Cumul");
    document.getElementById("OverBusy").setAttribute("value", getXMLValue(xmlData, "OverBusy"));
    document.getElementById("EnableCumul").checked = getXMLValue(xmlData, "Cumul");
    document.getElementById("Sensibility").setAttribute("value", getXMLValue(xmlData, "Sensi"));
    document.getElementById("PowerSupply").checked = getXMLValue(xmlData, "Power");
    document.getElementById("BillAccepted").checked = getXMLValue(xmlData, "Bill");
}

function updateTubes(xmlData)
{
    if (!xmlData)
    {
        return;
    }
    document.getElementById('Lev0').innerHTML = getXMLValue(xmlData, 'Lev0');
    document.getElementById('Lev0').className = "bar-in-" + getXMLValue(xmlData, "status0");

    document.getElementById('Lev1').innerHTML = getXMLValue(xmlData, 'Lev1');
    document.getElementById('Lev1').className = "bar-in-" + getXMLValue(xmlData, "status1");

    document.getElementById('Lev2').className = "bar-in-" + getXMLValue(xmlData, "status2");
    document.getElementById('Lev2').innerHTML = getXMLValue(xmlData, 'Lev2');

    document.getElementById('Lev3').className = "bar-in-" + getXMLValue(xmlData, "status3");
    document.getElementById('Lev3').innerHTML = getXMLValue(xmlData, 'Lev3');

    document.getElementById('Lev4').className = "bar-in-" + getXMLValue(xmlData, "status4");
    document.getElementById('Lev4').innerHTML = getXMLValue(xmlData, 'Lev4');

    document.getElementById('Lev5').className = "bar-in-" + getXMLValue(xmlData, "status5");
    document.getElementById('Lev5').innerHTML = getXMLValue(xmlData, 'Lev5');

    document.getElementById('Lev6').className = "bar-in-" + getXMLValue(xmlData, "status6");
    document.getElementById('Lev6').innerHTML = getXMLValue(xmlData, 'Lev6');

    document.getElementById('Lev7').className = "bar-in-" + getXMLValue(xmlData, "status7");
    document.getElementById('Lev7').innerHTML = getXMLValue(xmlData, 'Lev7');

    document.getElementById('Lev8').className = "bar-in-" + getXMLValue(xmlData, "status8");
    document.getElementById('Lev8').innerHTML = getXMLValue(xmlData, 'Lev8');

    document.getElementById('Lev9').className = "bar-in-" + getXMLValue(xmlData, "status9");
    document.getElementById('Lev9').innerHTML = getXMLValue(xmlData, 'Lev9');

    document.getElementById('Lev10').className = "bar-in-" + getXMLValue(xmlData, "status10");
    document.getElementById('Lev10').innerHTML = getXMLValue(xmlData, 'Lev10');

    document.getElementById('Lev11').className = "bar-in-" + getXMLValue(xmlData, "status11");
    document.getElementById('Lev11').innerHTML = getXMLValue(xmlData, 'Lev11');

    document.getElementById('Lev12').className = "bar-in-" + getXMLValue(xmlData, "status12");
    document.getElementById('Lev12').innerHTML = getXMLValue(xmlData, 'Lev12');

    document.getElementById('Lev13').className = "bar-in-" + getXMLValue(xmlData, "status13");
    document.getElementById('Lev13').innerHTML = getXMLValue(xmlData, 'Lev13');

    document.getElementById('Lev14').className = "bar-in-" + getXMLValue(xmlData, "status14");
    document.getElementById('Lev14').innerHTML = getXMLValue(xmlData, 'Lev14');

    document.getElementById('Lev15').className = "bar-in-" + getXMLValue(xmlData, "status15");
    document.getElementById('Lev15').innerHTML = getXMLValue(xmlData, 'Lev15');

    document.getElementById('total').innerHTML = getXMLValue(xmlData, 'total');
}

function updateActivation(xmlData)
{
    var strIndex = getXMLValue(xmlData, 'nummch');
    document.getElementById('Act' + strIndex).innerHTML = getXMLValue(xmlData, 'numact');
}

function updateStatus(xmlData)
{
    document.getElementById('timeCentrale').innerHTML = getXMLValue(xmlData, 'CentralTime');
}

function getMachineParameters()
{
    newAJAXCommand('maparams.xml?NumMachine=' + selection.options[selection.selectedIndex].value, updateParameters, false, null, false);
}

function getTimeCentral()
{
    setTimeout("newAJAXCommand('timeCentrale.xml', updateStatus, true)", 1000);
}

function getTubesLevel()
{
    newAJAXCommand('tubes.xml', updateTubes, true);
}

function getHistorique(dir)
{
    newAJAXCommand('dir.cgi?direction=' + dir.toString(), null, false, null, false);

    for (IndexHisto = 1; IndexHisto <= 20; IndexHisto++)
    {
        newAJAXCommand('hist.xml?Index=' + IndexHisto.toString(), updateHistorique, false, null, false);
    }
}

function getDateTimeSystem()
{
    var strTimeSystem, strDateSystem;
    var now = new Date();
    var lTimeSystem = ((now.getSeconds() % 10) + ((now.getSeconds() / 10) << 4) +
            ((now.getMinutes() % 10) << 8) + ((now.getMinutes() / 10) << 12) +
            ((now.getHours() % 10) << 16) + ((now.getHours() / 10) << 20) << 8);
    var lDateSystem = ((now.getDate() % 10) + ((now.getDate() / 10) << 4) +
            (((now.getMonth() + 1) % 10) << 8) + (((now.getMonth() + 1) / 10) << 12) +
            (((now.getFullYear() - 2000) % 10) << 16) + (((now.getFullYear() - 2000) / 10) << 20) << 8);

    document.getElementById('Time').setAttribute('value', strTimeSystem = lTimeSystem.toString());
    document.getElementById('Date').setAttribute('value', strDateSystem = lDateSystem.toString());
}

function getNumAct(numMach)
{
    newAJAXCommand('act.xml?numMach=' + numMach.toString(), updateActivation, false, null, true);
}

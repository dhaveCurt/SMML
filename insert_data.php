<?php
$conn = new mysqli('localhost', 'root', '', 'smml');  // Use the smml database

// Check the connection
if ($conn->connect_error) {
    die('Connection failed: ' . $conn->connect_error);
}

// Get POST data
$deviceID = $_POST['deviceID'];
$phVal = $_POST['phVal'];
$nVal = $_POST['nVal'];
$pVal = $_POST['pVal'];
$kVal = $_POST['kVal'];
$tempVal = $_POST['tempVal'];
$ecVal = $_POST['ecVal'];
$moistVal = $_POST['moistVal'];

// Step 1: Check if the device exists in the device table
$sql_check_device = "SELECT deviceID FROM device WHERE deviceID = ?";
$stmt_check_device = $conn->prepare($sql_check_device);
$stmt_check_device->bind_param('i', $deviceID);
$stmt_check_device->execute();
$stmt_check_device->store_result();

if ($stmt_check_device->num_rows == 0) {
    // Device doesn't exist, return an error or insert the device into the `device` table
    echo 'Error: Device not found in the device table. Please check the deviceID.';
    exit;  // Stop further execution if device does not exist
}

$stmt_check_device->close();

// Step 2: Insert the sensor data into the sensordata table
$sql = "INSERT INTO sensordata (deviceID, phVal, nVal, pVal, kVal, tempVal, ecVal, moistVal) 
        VALUES (?, ?, ?, ?, ?, ?, ?, ?)";

$stmt = $conn->prepare($sql);
$stmt->bind_param('iddddddd', $deviceID, $phVal, $nVal, $pVal, $kVal, $tempVal, $ecVal, $moistVal);

if ($stmt->execute()) {
    echo 'Data inserted successfully';
} else {
    echo 'Error: ' . $stmt->error;
}

// Close the statement and connection
$stmt->close();
$conn->close();
?>

import SensorDataModel from "@/app/models/SensorDataModel";
import connectDB from "@/services/mongo";
import { NextRequest, NextResponse } from "next/server";

//insert data
export async function POST(req: NextRequest) {
  try {
    connectDB();

    const requestData = await req.json();

    const { Vitesse, Pluie, Accident } = requestData;

    // Create a new instance of SensorDataModel
    const sensorData = new SensorDataModel({
      Vitesse,
      Pluie,
      Accident,
    });

    // Save the data to the database
    await sensorData.save();

    if (Accident == 1) {
      var myHeaders = new Headers();
      myHeaders.append("Content-Type", "application/json");

      var raw = JSON.stringify({
        text: "Un Nouvel accident a été renseigné.\nFaite le nécessaire puis appuyer sur OK pour retirer la notification",
      });

      var requestOptions = {
        method: "POST",
        headers: myHeaders,
        body: raw,
      };

      await fetch("http://localhost:3001/sendNotification", requestOptions);
    }

    // Return the response
    return NextResponse.json(
      { success: true, message: "POST request handled successfully" },
      { status: 200 }
    );
  } catch (error) {
    console.error("Failed to handle POST request:", error);
    // Return an error response if necessary
  }
}

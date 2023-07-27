import { NextRequest, NextResponse } from "next/server";
import connectDB from "@/services/mongo";
import SensorDataModel, { ISensorData } from "@/app/models/SensorDataModel";
import { IAccidentRainInfo } from "@/interfaces/IAccidentRainInfo";

export async function GET() {
  try {
    connectDB();

    // Query the data from the database using the DataModel
    const totalAccident = await SensorDataModel.find({ Accident: 1 });

    const numberOfAccidentWithRain = totalAccident.filter((data) =>
      data.Pluie.every((value) => value === 1)
    ).length;

    const numberOfAccidentWithoutRain =
      totalAccident.length - numberOfAccidentWithRain;

    const data = {
      totalNumberOfAccident: totalAccident.length,
      numberOfAccidentWithRain: numberOfAccidentWithRain,
      numberOfAccidentWithoutRain: numberOfAccidentWithoutRain,
    };

    // Return the response with the fetched data
    return NextResponse.json({ data }, { status: 200 });
  } catch (error) {
    console.error("Failed to fetch data:", error);
    // Return an error response if necessary
  }
}

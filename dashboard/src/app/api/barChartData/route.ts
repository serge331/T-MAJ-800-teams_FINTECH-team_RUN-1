import { NextResponse } from "next/server";
import connectDB from "@/services/mongo";
import SensorDataModel, { ISensorData } from "@/app/models/SensorDataModel";
import { IAccidentSpeedInfo } from "@/interfaces/IAccidentSpeedInfo";

function getAccidentForSpeed(
  sensorData: ISensorData[],
  repartitionSpeed: number[],
  speed: number
): number {
  return sensorData.filter(
    (data) =>
      data.Accident === 1 &&
      data.Vitesse.every((value) => value <= repartitionSpeed[speed])
  ).length;
}

export async function GET() {
  try {
    connectDB();

    // Query the data from the database using the DataModel
    const totalAccident = await SensorDataModel.find({ Accident: 1 });

    // Perform any required data manipulation or processing
    const repartitionSpeed: number[] = [50, 80, 100, 140];
    const accidentFor50 = getAccidentForSpeed(
      totalAccident,
      repartitionSpeed,
      0
    );
    const accidentFor80 = getAccidentForSpeed(
      totalAccident,
      repartitionSpeed,
      1
    );
    const accidentFor100 = getAccidentForSpeed(
      totalAccident,
      repartitionSpeed,
      2
    );
    const accidentFor140 = getAccidentForSpeed(
      totalAccident,
      repartitionSpeed,
      3
    );

    const data: IAccidentSpeedInfo = {
      accidentFor50,
      accidentFor80,
      accidentFor100,
      accidentFor140,
    };

    // Return the response with the fetched data
    return NextResponse.json({ data }, { status: 200 });
  } catch (error) {
    console.error("Failed to fetch data:", error);
    // Return an error response if necessary
  }
}

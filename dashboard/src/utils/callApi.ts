import { IAccidentRainInfo } from "@/interfaces/IAccidentRainInfo";
import { IAccidentSpeedInfo } from "@/interfaces/IAccidentSpeedInfo";

export async function getAccidentRainInfo() {
  const result = await fetch("/api/pieChartData");
  const resultJson = await result.json();
  const data: IAccidentRainInfo = resultJson.data;

  return data;
}

export async function getAccidentSpeedInfo() {
  const result = await fetch("/api/barChartData");
  const resultJson = await result.json();
  const data: IAccidentSpeedInfo = resultJson.data;
  return data;
}

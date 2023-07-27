"use client";

import React from "react";
import {
  Chart as ChartJS,
  CategoryScale,
  LinearScale,
  PointElement,
  LineElement,
  Title,
  Tooltip,
  Legend,
  ChartOptions,
} from "chart.js";
import { Line } from "react-chartjs-2";
import { IAccidentSpeedInfo } from "@/app/api/barChartData/route";

ChartJS.register(
  CategoryScale,
  LinearScale,
  PointElement,
  LineElement,
  Title,
  Tooltip,
  Legend
);

const options: ChartOptions<"line"> = {
  responsive: true,
  plugins: {
    legend: {
      position: "top" as const,
    },
    title: {
      display: true,
      text: "Corrélation entre la vitesse et l'augmentation des accidents",
    },
  },
  scales: {
    x: {
      display: true,
      title: {
        display: true,
        text: "Vitesse (km/h)",
      },
    },
    y: {
      display: true,
      title: {
        display: true,
        text: "Nombre d'accidents",
      },
    },
  },
};

export function LineChartComponent({
  accidentFor50,
  accidentFor80,
  accidentFor100,
  accidentFor140,
}: IAccidentSpeedInfo) {
  const data = {
    labels: ["50", "80", "100", "140"],
    datasets: [
      {
        label: "Accident",
        data: [accidentFor50, accidentFor80, accidentFor100, accidentFor140],
        borderColor: "rgb(75, 192, 192)",
        backgroundColor: "rgba(75, 192, 192, 0.5)",
      },
    ],
  };

  return <Line options={options} data={data} />;
}

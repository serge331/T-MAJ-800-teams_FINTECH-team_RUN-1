"use client";

import {
  Chart as ChartJS,
  ArcElement,
  Legend,
  Tooltip,
  ChartOptions,
} from "chart.js";
import { set } from "mongoose";
import React, { useEffect, useState } from "react";
import { Pie } from "react-chartjs-2";

ChartJS.register(ArcElement, Tooltip, Legend);

interface PieChartData {
  label: string;
  number: number;
  color: string;
}
interface IPieChartComponentProps {
  data: PieChartData[];
  title: string;
  legendPosition: "top" | "left" | "bottom" | "right";
}

function buildPieChartOptions(
  title: string,
  legendPosition: "top" | "left" | "bottom" | "right" = "top"
) {
  return {
    plugins: {
      title: {
        display: true,
        text: title,
      },
      legend: {
        display: true,
        position: legendPosition,
      },
    },
  };
}
function buildPieChartData(data: PieChartData[]) {
  const labels = data.map((d) => d.label);
  const numbers = data.map((d) => d.number);
  const colors = data.map((d) => d.color);

  return {
    labels: labels,
    datasets: [
      {
        label: "Nombre d'accidents",
        data: numbers,
        backgroundColor: colors,
        borderColor: colors,
        borderWidth: 1,
      },
    ],
  };
}

function PieChartComponent({
  data,
  title,
  legendPosition,
}: IPieChartComponentProps) {
  const [chartData, setChartData] = useState(buildPieChartData(data));
  const [chartOptions, setChartOptions] = useState<ChartOptions<"pie">>(
    buildPieChartOptions(title, legendPosition)
  );

  return <Pie data={chartData} options={chartOptions} />;
}

export default PieChartComponent;

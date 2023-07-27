"use client";
import { LineChartComponent } from "@/components/LineChartComponent";
import ChartComponent from "@/components/PieChartComponent";
import React, { useEffect, useState } from "react";
import { getAccidentRainInfo, getAccidentSpeedInfo } from "@/utils/callApi";
import { IAccidentRainInfo } from "@/interfaces/IAccidentRainInfo";
import { IAccidentSpeedInfo } from "@/interfaces/IAccidentSpeedInfo";
import socketIOClient, { Socket } from "socket.io-client";

const socketIO = socketIOClient("http://localhost:3001"); // Replace with the URL of your Socket.IO server

function ChartsPage() {
  const [accidentRainInfo, setAccidentRainInfo] =
    useState<IAccidentRainInfo | null>(null);
  const [accidentSpeedInfo, setAccidentSpeedInfo] =
    useState<IAccidentSpeedInfo | null>(null);

  const [socket, setSocket] = useState<Socket>(socketIO);

  const [notification, setNotification] = useState<string | null>(null);

  useEffect(() => {
    async function getData() {
      const accidentRainInfo = await getAccidentRainInfo();
      const accidentSpeedInfo = await getAccidentSpeedInfo();

      setAccidentRainInfo(accidentRainInfo);
      setAccidentSpeedInfo(accidentSpeedInfo);
    }

    getData();
  }, []);

  useEffect(() => {
    if (socket == null) return;

    socket.on("notification", (data: string) => {
      setNotification(data);
    });

    return () => {
      socket.disconnect(); // Disconnect the Socket.IO client when the component is unmounted
    };
  }, [socket]);

  function returnLoading() {
    return (
      <div className="flex items-center justify-center flex-col">
        <svg
          xmlns="http://www.w3.org/2000/svg"
          fill="none"
          viewBox="0 0 24 24"
          strokeWidth={1.5}
          stroke="black"
          className="w-10 h-10 animate-spin"
        >
          <path
            strokeLinecap="round"
            strokeLinejoin="round"
            d="M16.023 9.348h4.992v-.001M2.985 19.644v-4.992m0 0h4.992m-4.993 0l3.181 3.183a8.25 8.25 0 0013.803-3.7M4.031 9.865a8.25 8.25 0 0113.803-3.7l3.181 3.182m0-4.991v4.99"
          />
        </svg>
        <p className="text-black">Chargement ...</p>
      </div>
    );
  }

  function returnPieChart() {
    if (accidentRainInfo == null) return returnLoading();

    return (
      <ChartComponent
        title="Nombre d'accidents en fonction de la météo"
        data={[
          {
            label: "Temps Pluvieux",
            number: accidentRainInfo.numberOfAccidentWithRain,
            color: "#4bc0c0",
          },
          {
            label: "Temps Ensoleillé",
            number: accidentRainInfo.numberOfAccidentWithoutRain,
            color: "#35a2eb",
          },
        ]}
        legendPosition="bottom"
      />
    );
  }

  function returnLineChart() {
    if (accidentSpeedInfo == null) return returnLoading();

    return (
      <LineChartComponent
        accidentFor50={accidentSpeedInfo.accidentFor50}
        accidentFor80={accidentSpeedInfo.accidentFor80}
        accidentFor100={accidentSpeedInfo.accidentFor100}
        accidentFor140={accidentSpeedInfo.accidentFor140}
      />
    );
  }

  function openModal() {
    if (notification == null) return;

    const response = confirm(notification);

    if (response) {
      setNotification(null);
    }
  }

  return (
    <div className="h-screen w-screen bg-white overflow-hidden relative">
      <div className="absolute w-full hidden lg:flex items-center justify-center flex-col my-10">
        <h1 className="text-3xl font-bold text-black mb-2">
          Rapport d'incidents
        </h1>
        <svg
          onClick={openModal}
          xmlns="http://www.w3.org/2000/svg"
          fill="none"
          viewBox="0 0 24 24"
          strokeWidth={1.5}
          stroke="black"
          className={`w-8 h-8  ${
            notification !== null ? "animate-bounce" : ""
          }`}
        >
          <path
            strokeLinecap="round"
            strokeLinejoin="round"
            d="M14.857 17.082a23.848 23.848 0 005.454-1.31A8.967 8.967 0 0118 9.75v-.7V9A6 6 0 006 9v.75a8.967 8.967 0 01-2.312 6.022c1.733.64 3.56 1.085 5.455 1.31m5.714 0a24.255 24.255 0 01-5.714 0m5.714 0a3 3 0 11-5.714 0"
          />
        </svg>
      </div>
      <div className="flex flex-col lg:flex-row justify-around h-full w-full lg:px-10">
        <div className="w-full lg:w-1/3 bg-white flex items-center justify-center">
          {returnPieChart()}
        </div>
        <div className="w-full lg:w-2/3 flex items-center justify-center">
          {returnLineChart()}
        </div>
      </div>
    </div>
  );
}

export default ChartsPage;

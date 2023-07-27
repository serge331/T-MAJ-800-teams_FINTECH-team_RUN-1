import mongoose, { Model, Schema } from "mongoose";

export interface ISensorData extends Document {
  Vitesse: number[];
  Pluie: number[];
  Accident: number;
}

const SensorDataSchema: Schema = new Schema({
  Vitesse: [Number],
  Pluie: [Number],
  Accident: Number,
});

let SensorDataModel: Model<ISensorData>;

try {
  SensorDataModel = mongoose.model<ISensorData>("sensor_datas");
} catch {
  SensorDataModel = mongoose.model<ISensorData>(
    "sensor_datas",
    SensorDataSchema
  );
}

export default SensorDataModel;

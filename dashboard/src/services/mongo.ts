import mongoose, { ConnectOptions } from "mongoose";

const connectDB = async (): Promise<void> => {
  try {
    await mongoose.connect(`${process.env.MONGODB_URI as string}`);
    console.log("Connected to MongoDB");
  } catch (error) {
    console.error("Failed to connect to MongoDB:", error);
  }
};

export default connectDB;

import joblib
import sys
import json

def load_model(model_path):
    try:
        model = joblib.load(model_path)
        return model
    except FileNotFoundError:
        print("Model file not found.")
        return None

def make_prediction(model, data):
    if model is None:
        print("Model not loaded.")
        return None

    try:
        prediction = model.predict(data)
        return prediction[0]
    except ValueError as e:
        print(f"Error: {str(e)}")
        return None

if __name__ == '__main__':
    if len(sys.argv) < 3:
        print("Please provide the path to the trained model and prediction data as a command-line argument.")
    else:
        # Specify the path to the trained model
        model_path = sys.argv[1]
        prediction_data = sys.argv[2]

        # Load the trained model
        model = load_model(model_path)

        if model is not None:
            # Convert the prediction data from a JSON string to a list of numbers
            prediction_data = json.loads(prediction_data)
            # Make a prediction using the loaded model
            prediction = make_prediction(model, prediction_data)

            if prediction is not None:
                print(prediction)

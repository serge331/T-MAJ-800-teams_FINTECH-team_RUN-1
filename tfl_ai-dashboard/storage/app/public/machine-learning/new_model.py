import pandas as pd
import json
from sklearn.linear_model import LogisticRegression
from sklearn.pipeline import make_pipeline
from sklearn.preprocessing import StandardScaler
import joblib
import sys

def train_model(file_path):
    # Load data from the CSV file
    data = pd.read_csv(file_path, sep=',')

    # Convert JSON strings to lists of numbers
    data['Vitesse'] = data['Vitesse'].apply(lambda x: json.loads(x))
    data['Pluie'] = data['Pluie'].apply(lambda x: json.loads(x))

    # Flatten the lists of numbers into individual columns
    data = pd.concat([data.drop(['Vitesse', 'Pluie'], axis=1), data['Vitesse'].apply(pd.Series), data['Pluie'].apply(pd.Series)], axis=1)

    # Split the data into features (X) and the target (y)
    X = data.drop('Accident', axis=1)
    y = data['Accident']

    # Create a pipeline with feature scaling and a logistic regression model
    pipeline = make_pipeline(StandardScaler(), LogisticRegression())

    # Train the model
    pipeline.fit(X, y)

    return pipeline

if __name__ == '__main__':
    if len(sys.argv) < 3:
        print("Please provide both the file path and output path as command-line arguments.")
    else:
        file_path = sys.argv[1]
        output_path = sys.argv[2]
        # Train the model
        model = train_model(file_path)

        # Export the trained model to the specified output path
        joblib.dump(model, output_path)

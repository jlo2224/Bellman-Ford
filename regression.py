import numpy as np
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression
from sklearn.preprocessing import FunctionTransformer

def load_data(filename):
    data = np.loadtxt(filename)
    x = data[:, 0].reshape(-1, 1)  # Reshape to be a 2D array for scikit-learn compatibility
    y = data[:, 4]
    return x, y

def perform_linear_regression(x, y):
    linear_regressor = LinearRegression()
    linear_regressor.fit(x, y)
    y_pred = linear_regressor.predict(x)
    return linear_regressor, y_pred

def perform_logarithmic_regression(x, y):
    log_transformer = FunctionTransformer(np.log1p, validate=True)  # log1p handles x = 0 correctly
    x_log = log_transformer.transform(x)
    log_regressor = LinearRegression()
    log_regressor.fit(x_log, y)
    y_log_pred = log_regressor.predict(x_log)
    return log_regressor, y_log_pred

def plot_data_and_regressions(x, y, y_linear_pred, y_log_pred):
    plt.figure(figsize=(10, 6))
    plt.scatter(x, y, color='blue', label='Data')
    plt.plot(x, y_linear_pred, color='red', label='Linear Regression')
    #plt.plot(x, y_log_pred, color='green', linestyle='dashed', label='Logarithmic Regression')
    plt.ylim(bottom=0)  # Force the minimum y-axis value to be 0
    plt.xlabel('# of Vertices')
    plt.ylabel('# of Successful Relaxations')
    plt.title('Successful Relaxations on Dense Graph (exponential dist.)')
    plt.legend()
    plt.show()


# Main function
def main():
    filename = 'graphs/long_exponential_dense.txt'  # Replace this with the path to your file
    
    # Load the data
    x, y = load_data(filename)
    
    linear_regressor, y_linear_pred = perform_linear_regression(x, y)
    
    log_regressor, y_log_pred = perform_logarithmic_regression(x, y)
    
    plot_data_and_regressions(x, y, y_linear_pred, y_log_pred)

if __name__ == "__main__":
    main()


from flask import Flask, jsonify, request
import sqlite3

app = Flask(__name__)

connect = sqlite3.connect('dormgarden.db')
connect.execute('''
    CREATE TABLE IF NOT EXISTS SOIL_LOGS (
    device_id INTEGER NOT NULL,
    plant_name TEXT NOT NULL,
    timestamp TEXT NOT NULL,
    moisture_reading INTEGER NOT NULL
    )
    ''')

# Get all books
@app.route('/plant_info', methods=['GET'])
def get_plant_info():
    plant_info = {"plant":"big plant"}
    return jsonify(plant_info)

# Add a sensor reading
@app.route('/plant_log', methods=['POST'])
def post_soil_log():
    try:
        soil_log = request.json
        with sqlite3.connect("dormgarden.db") as plant_logs:
            cursor = plant_logs.cursor()
            cursor.execute("INSERT INTO SOIL_LOGS \
            (device_id,plant_name,timestamp,moisture_reading) VALUES (?,?,?,?)",
                           (soil_log.get("device_id"), soil_log.get("plant_name"), soil_log.get("timestamp"), soil_log.get("moisture_reading")))
            plant_logs.commit()
    except:
        invalid_params_err = {
            "error" : "invalid json body"
        }
        return jsonify(invalid_params_err), 400
    return soil_log, 201


if __name__ == '__main__':
    app.run(host='10.24.105.175', port=9147 , debug=True)

import matplotlib.pyplot as plt
import numpy as np

from collections import deque #double-ended queue)

class PID:
  def __init__(self, Kp, Ki, Kd, setpoint=0, history_len=50, derivative_points=5):
    self.Kp = Kp
    self.Ki = Ki
    self.Kd = Kd
    self.setpoint = setpoint

    self.error_history = deque(maxlen=history_len)
    self.time_history = deque(maxlen=history_len)
    self.derivative_points = derivative_points

  def update(self, measurement, dt):
    error = self.setpoint - measurement

    self.error_history.append(error)
    self.time_history.append(dt)

    # --- Integral: Sum over all stored errors
    integral = sum(e * t for e, t in zip(self.error_history, self.time_history))

    # --- Derivative: Use only the last N points
    if len(self.error_history) >= self.derivative_points:
        # Get last N errors and times
        recent_errors = list(self.error_history)[-self.derivative_points:]
        recent_times = list(self.time_history)[-self.derivative_points:]
        delta_error = recent_errors[-1] - recent_errors[0]
        total_time = sum(recent_times)
        derivative = delta_error / total_time if total_time > 0 else 0
    else:
        derivative = 0

    # --- Output
    output = self.Kp * error + self.Ki * integral + self.Kd * derivative
    return output
  

#============================
setpoint = 10
dt = 0.1
time_steps = 200

pid = PID(Kp=1.2, Ki=0.0, Kd=0.0, setpoint=setpoint)

# Simulation state
process_value = 0

# History for plotting
times = []
values = []
outputs = []
errors = []

# Run simulation
for i in range(time_steps):
  time = i * dt
  output = pid.update(process_value, dt)

  # Simulate response (simple + noise)
  process_value += output * dt + np.random.normal(0, 0.1)

  # Record data
  times.append(time)
  values.append(process_value)
  outputs.append(output)
  errors.append(setpoint - process_value)
  
  # Print for debugging
  print(f"Time: {time:5.2f}, Process Value: {process_value:7.2f}, Output: {output:6.2f}, Error: {errors[-1]:6.2f}")

# --- Plotting ---
plt.figure(figsize=(12, 6))

plt.subplot(2, 1, 1)
plt.plot(times, values, label="Process Variable", linewidth=2)
plt.axhline(setpoint, color='r', linestyle='--', label="Setpoint")
plt.title("PID Control Simulation")
plt.ylabel("Value")
plt.legend()
plt.grid(True)

plt.subplot(2, 1, 2)
plt.plot(times, outputs, label="Control Output (PID)", color='purple')
plt.xlabel("Time (s)")
plt.ylabel("Control Signal")
plt.legend()
plt.grid(True)

plt.tight_layout()
plt.show()
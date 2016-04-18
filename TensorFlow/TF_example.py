#!/usr/local/bin/python

#inside python, 
#execfile("TF_example.py")


#--------- load the one_hot True data
import input_data
mnist = input_data.read_data_sets("MNIST_data/", one_hot=True)

#--------- import TensorFlow
import tensorflow as tf

#--------- the array fo vector that we ask TensorFlow to compute
x = tf.placeholder(tf.float32, [None, 784])

#--------- a simple model, y = W.x + b, y will be 0 to 9, which is the label of the picture
W = tf.Variable(tf.zeros([784, 10]))
b = tf.Variable(tf.zeros([10]))
y = tf.nn.softmax(tf.matmul(x, W) + b)

#-------- true distribution
y_ = tf.placeholder(tf.float32, [None, 10])

#-------- entropy function
cross_entropy = -tf.reduce_sum(y_*tf.log(y))

#------- training, using Gradient Descent Method with step 0.01, minimize entropy
train_step = tf.train.GradientDescentOptimizer(0.01).minimize(cross_entropy)

#------- an operation to inintialize all variable
init = tf.initialize_all_variables()

#------- Start a TensorFlow Session
sess = tf.Session()
#------- run the operation -- init
sess.run(init)

#------ train for 1000.
#------ in each loop, get 100 random data points
#------ replace the x and y_ by the random data points
for i in range(1000):
  batch_xs, batch_ys = mnist.train.next_batch(100)
  sess.run(train_step, feed_dict={x: batch_xs, y_: batch_ys})


#------ compare the Model and True data
#------ argmax(y,1) is the most likely for each input
#------ argmax(y_,1) is the correct label
#------ This gives an array of 1/0 for true/false
correct_prediction = tf.equal(tf.argmax(y,1), tf.argmax(y_,1))

#------ compute the precentage of correct
accuracy = tf.reduce_mean(tf.cast(correct_prediction, "float"))

#------ Print out the accuracy for test.images, and mnist.image
print(sess.run(accuracy, feed_dict={x: mnist.test.images, y_: mnist.test.labels}))

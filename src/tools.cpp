#include "tools.h"
#include <iostream>

using Eigen::VectorXd;
using Eigen::MatrixXd;
using std::vector;

Tools::Tools() {}

Tools::~Tools() {}

VectorXd Tools::CalculateRMSE(const vector<VectorXd> &estimations,
                              const vector<VectorXd> &ground_truth) {
  /**
   * TODO: Calculate the RMSE here.
   */
	VectorXd d(4);

	
	d << 0, 0, 0, 0;

	// check the validity of the following inputs:
	//  * the estimation vector size should not be zero
	//  * the estimation vector size should equal ground truth vector size
	if (estimations.size() != ground_truth.size()
		|| estimations.size() == 0) {
		
		return d;
	}

	// accumulate squared residuals
	for (unsigned int i = 0; i < estimations.size(); ++i) {
		
		VectorXd residual = estimations[i] - ground_truth[i];

		// coefficient-wise multiplication
		residual = residual.array()*residual.array();
		d += residual;
	}
	
	// calculate the mean
	d = d / estimations.size();

	// calculate the squared root
	d = d.array().sqrt();

	// return the result
	
	return d;
}

MatrixXd Tools::CalculateJacobian(const VectorXd& x_state) {
  /**
   * TODO:
   * Calculate a Jacobian here.
   */
	

	MatrixXd m(3, 4);
	// recover state parameters
	float px = x_state(0);
	float py = x_state(1);
	float vx = x_state(2);
	float vy = x_state(3);

	// pre-compute a set of terms to avoid repeated calculation
	float c1 = px*px + py*py;
	float c2 = sqrt(c1);
	float c3 = (c1*c2);

	// check division by zero
	if (fabs(c1) < 0.0001) {
		
		return m;
	}

	// compute the Jacobian matrix
	m << (px / c2), (py / c2), 0, 0,
		-(py / c1), (px / c1), 0, 0,
		py*(vx*py - vy*px) / c3, px*(px*vy - py*vx) / c3, px / c2, py / c2;

	return m;
}

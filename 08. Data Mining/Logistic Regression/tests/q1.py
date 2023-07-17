OK_FORMAT = True

test = {   'name': 'q1',
    'points': 2,
    'suites': [   {   'cases': [   {'code': '>>> sum(lr.predict(x_test) == y_test) == 130\nTrue', 'hidden': True, 'locked': False},
                                   {'code': '>>> np.isclose(train_accuracy, 0.8709, atol=1e-4)\nTrue', 'hidden': True, 'locked': False},
                                   {'code': '>>> np.isclose(test_accuracy, 0.9091, atol=1e-4)\nTrue', 'hidden': True, 'locked': False}],
                      'scored': True,
                      'setup': '',
                      'teardown': '',
                      'type': 'doctest'}]}

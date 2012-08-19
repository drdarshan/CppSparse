import cppsparse, unittest, ch4

class TestCholesky(unittest.TestCase):
    def setUp(self):
        self.A = ch4.matrix

    def testEliminationTree(self):
        etree = self.A.etree_liu();
        self.assertEqual(list(etree)[1:-1], [6, 3, 8, 6, 8, 7, 9, 10, 10, 11])

    def testReach(self):
        etree           = self.A.etree_liu();
        reachesActual   = [list(self.A.ereach2(etree, j)) for j in range(6, 12)]
        reachesExpected = [[1, 4], [1, 6], [2, 3, 5], [6, 7], [3, 8, 4, 6, 7, 9], [3, 8, 10, 5, 7, 9]]
        self.assertEqual(reachesExpected, reachesActual)
    
if __name__=="__main__":
    unittest.main()

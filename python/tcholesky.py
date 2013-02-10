import cppsparse, unittest, ch4

class TestCholesky(unittest.TestCase):
    def setUp(self):
        self.A = ch4.matrix
        self.parent = [6, 3, 8, 6, 8, 7, 9, 10, 10, 11]
        self.rowcounts = [1, 1, 1, 2, 1, 1, 3, 3, 4, 3, 7, 7]
        self.colcounts = [1, 3, 3, 4, 3, 3, 4, 4, 3, 3, 2, 1]
        
    def testEliminationTree(self):
        etree = self.A.etree_liu();
        self.assertEqual(list(etree)[1:-1], self.parent)

    def testReach(self):
        etree           = self.A.etree_liu();
        reachesActual   = [list(self.A.ereach2(etree, j)) for j in range(6, 12)]
        reachesExpected = [[1, 4], [1, 6], [2, 3, 5], [6, 7], [3, 8, 4, 6, 7, 9], [3, 8, 10, 5, 7, 9]]
        self.assertEqual(reachesExpected, reachesActual)
        
    def testPostorder(self):
        etree = self.A.etree_liu()
        post  = list(self.A.postorder(etree))
        self.assertEqual([2, 3, 5, 8, 1, 4, 6, 7, 9, 10, 11], post[1:])

    def testFirstDescenentLevel(self):
        etree = self.A.etree_liu()
        post  = self.A.postorder(etree)
        first = cppsparse.ivec()
        level = cppsparse.ivec()
        self.A.first_descendent(etree, post, first, level)

        self.assertEqual([0, 5, 1, 1, 6, 3, 5, 5, 1, 5, 1, 1], list(first))
        self.assertEqual([0, 5, 4, 3, 5, 3, 4, 3, 2, 2, 1, 0], list(level))

    def testRowCounts(self):
        etree  = self.A.etree_liu()
        post   = self.A.postorder(etree)
        rowcnt = self.A.row_counts(etree, post)
        
        self.assertEqual(self.rowcounts, list(rowcnt))

    def testColumnCounts(self):
        etree  = self.A.etree_liu()
        post   = self.A.postorder(etree)
        colcnt = self.A.column_counts(etree, post)
        
        self.assertEqual(self.colcounts, list(colcnt))

    def testEtreeRowColCounts(self):
        parent, rowcnt, colcnt = cppsparse.ivec(), cppsparse.ivec(), cppsparse.ivec()

        self.A.etree_row_column_counts(parent, rowcnt, colcnt)
        
        self.assertEqual(self.parent, list(parent)[1:-1])
        self.assertEqual(self.rowcounts, list(rowcnt))
        self.assertEqual(self.colcounts, list(colcnt))
        
        

if __name__=="__main__":
    unittest.main()

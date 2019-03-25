<template>
  <el-table
    :data="tableData"
    border
    style="width: 100%">
    <el-table-column
      fixed
      sortable
      prop="number"
      label="车次"
      width="80">
    </el-table-column>
    <el-table-column
      prop="departure"
      label="出发站"
      width="90"
      :filters="departureFilters"
      :filter-method="filterHandler">
    </el-table-column>
    <el-table-column
      prop="arrival"
      label="到达站"
      width="90"
      :filters="arrivalFilters"
      :filter-method="filterHandler">
    </el-table-column>
    <el-table-column
      sortable
      prop="departureTime"
      label="出发时间"
      width="120">
    </el-table-column>
    <el-table-column
      sortable
      prop="arrivalTime"
      label="到达时间"
      width="120">
    </el-table-column>
    <el-table-column
      sortable
      prop="cost"
      label="历时"
      width="90">
    </el-table-column>
    <el-table-column
      prop="businessClass"
      label="商务座"
      width="90">
    </el-table-column>
    <el-table-column
      prop="firstClass"
      label="一等座"
      width="90">
    </el-table-column>
    <el-table-column
      prop="secondClass"
      label="二等座"
      width="90">
    </el-table-column>
    <el-table-column
      prop="sleepingClass"
      label="动卧"
      width="90">
    </el-table-column>
    <el-table-column
      prop="noSeat"
      label="无座"
      width="90">
    </el-table-column>
    <el-table-column
      fixed="right"
      label="操作"
      width="120">
      <template>
        <el-button type="primary" size="mini">预定</el-button>
      </template>
    </el-table-column>
  </el-table>
</template>


<script>
  export default {
    name: 'main-page',
    methods: {
      open (link) {
        this.$electron.shell.openExternal(link)
      },
      onSubmit () {
        alert('submit!')
      },
      deleteRow (index, rows) {
        rows.splice(index, 1)
      },
      resetDateFilter () {
        this.$refs.filterTable.clearFilter('date')
      },
      clearFilter () {
        this.$refs.filterTable.clearFilter()
      },
      formatter (row, column) {
        return row.address
      },
      filterTag (value, row) {
        return row.tag === value
      },
      filterHandler (value, row, column) {
        const property = column['property']
        return row[property] === value
      }
    },
    data () {
      return {
        tableData: [{
          number: 'G1',
          departure: '北京南',
          arrival: '上海虹桥',
          departureTime: '9:00',
          arrivalTime: '13:28',
          cost: '04:28',
          businessClass: 100,
          firstClass: 100,
          secondClass: 100,
          sleepingClass: 100,
          noSeat: 100
        }, {
          number: 'G5',
          departure: '北京南',
          arrival: '上海虹桥',
          departureTime: '7:00',
          arrivalTime: '13:08',
          cost: '05:48',
          businessClass: 100,
          firstClass: 10,
          secondClass: 100,
          sleepingClass: 100,
          noSeat: 100
        }
        ],
        departureFilters: [{text: '北京南', value: '北京南'}, {text: '北京', value: '北京'}],
        arrivalFilters: [{text: '上海虹桥', value: '上海虹桥'}, {text: '上海', value: '上海'}]
      }
    }
  }
</script>

<style>
  
</style>
